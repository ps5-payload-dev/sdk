/* Copyright (C) 2026 John Törnblom

This program is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 3, or (at your option) any
later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; see the file COPYING. If not, see
<http://www.gnu.org/licenses/>.  */

#include <errno.h>
#include <fcntl.h>
#include <poll.h>
#include <pthread.h>
#include <signal.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/socket.h>
#include <sys/ttycom.h>
#include <termios.h>
#include <unistd.h>

#include "ld.h"
#include "upty.h"


#define UPTY_MAX      8
#define UPTY_MAX_FDS  32
#define UPTY_MAGIC    0x75707479
#define UPTY_POLL_MS  10


typedef struct upty_shared {
  volatile int   lock;
  unsigned int   magic;
  unsigned int   gen;
  struct termios tio;
  struct winsize ws;
  int            pgrp;
  int            sid;
} upty_shared_t;


struct upty {
  int             used;
  upty_shared_t  *sh;
  upty_shared_t   priv;
  int             shm_fd;
  char            shm_name[64];
  int             ctl_fd;
  int             mfd;
  int             sfd;
  pthread_t       pump;
  int             pump_run;
  ld_t            ld;
};


static upty_t g_pty[UPTY_MAX];

static struct {
  int     fd;
  upty_t *pty;
} g_fds[UPTY_MAX_FDS];

static volatile int g_lock;
static int g_env_done;


int _ioctl(int fd, unsigned long request, ...);


static void
spin_lock(volatile int *lock) {
  while(__atomic_test_and_set(lock, __ATOMIC_ACQUIRE)) {
    __builtin_ia32_pause();
  }
}


static void
spin_unlock(volatile int *lock) {
  __atomic_clear(lock, __ATOMIC_RELEASE);
}


static void
upty_mirror_out(upty_t *pty) {
  upty_shared_t msg;

  if(pty->ctl_fd < 0) {
    return;
  }

  msg = *pty->sh;
  msg.lock = 0;
  send(pty->ctl_fd, &msg, sizeof(msg), MSG_DONTWAIT | MSG_NOSIGNAL);
}


static void
upty_mirror_in(upty_t *pty) {
  upty_shared_t msg;

  if(pty->ctl_fd < 0) {
    return;
  }

  while(recv(pty->ctl_fd, &msg, sizeof(msg), MSG_DONTWAIT) ==
	(ssize_t)sizeof(msg)) {
    if(msg.magic != UPTY_MAGIC || msg.gen < pty->sh->gen) {
      continue;
    }

    pty->sh->gen = msg.gen;
    pty->sh->tio = msg.tio;
    pty->sh->ws = msg.ws;
    pty->sh->pgrp = msg.pgrp;
    pty->sh->sid = msg.sid;
  }
}


static void
upty_state_lock(upty_t *pty) {
  spin_lock(&pty->sh->lock);
  upty_mirror_in(pty);
}


static void
upty_state_unlock(upty_t *pty) {
  spin_unlock(&pty->sh->lock);
}


static void
upty_publish(upty_t *pty) {
  pty->sh->gen++;
  upty_mirror_out(pty);
}


static upty_t*
upty_lookup_locked(int fd) {
  if(fd < 0) {
    return 0;
  }

  for(int i=0; i<UPTY_MAX_FDS; i++) {
    if(g_fds[i].pty && g_fds[i].fd == fd) {
      return g_fds[i].pty;
    }
  }

  return 0;
}


static int
upty_bind_locked(upty_t *pty, int fd) {
  if(upty_lookup_locked(fd)) {
    errno = EBUSY;
    return -1;
  }

  for(int i=0; i<UPTY_MAX_FDS; i++) {
    if(!g_fds[i].pty) {
      g_fds[i].fd = fd;
      g_fds[i].pty = pty;
      return 0;
    }
  }

  errno = EMFILE;
  return -1;
}


static upty_t*
upty_alloc_locked(void) {
  upty_t *pty = 0;

  for(int i=0; i<UPTY_MAX; i++) {
    if(!g_pty[i].used) {
      pty = &g_pty[i];
      break;
    }
  }

  if(!pty) {
    errno = ENOSPC;
    return 0;
  }

  memset(pty, 0, sizeof(*pty));
  pty->used = 1;
  pty->ctl_fd = -1;
  pty->shm_fd = -1;
  pty->mfd = -1;
  pty->sfd = -1;
  pty->sh = &pty->priv;
  pty->sh->magic = UPTY_MAGIC;
  pty->sh->sid = (int)getsid(0);
  pty->sh->pgrp = (int)getpgrp();
  pty->sh->ws.ws_row = 24;
  pty->sh->ws.ws_col = 80;
  cfmakesane(&pty->sh->tio);

  return pty;
}


static int
upty_shm_create(upty_t *pty) {
  upty_shared_t *sh;
  int fd;

  snprintf(pty->shm_name, sizeof(pty->shm_name), "/upty.%d.%d",
	   (int)getpid(), (int)(pty - g_pty));

  shm_unlink(pty->shm_name);

  if((fd=shm_open(pty->shm_name, O_RDWR | O_CREAT | O_EXCL, 0600)) < 0) {
    pty->shm_name[0] = 0;
    return -1;
  }

  if(ftruncate(fd, sizeof(*sh))) {
    close(fd);
    shm_unlink(pty->shm_name);
    pty->shm_name[0] = 0;
    return -1;
  }

  sh = mmap(0, sizeof(*sh), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  if(sh == MAP_FAILED) {
    close(fd);
    shm_unlink(pty->shm_name);
    pty->shm_name[0] = 0;
    return -1;
  }

  *sh = pty->priv;
  sh->lock = 0;
  pty->sh = sh;
  pty->shm_fd = fd;

  return 0;
}


static int
upty_shm_attach(upty_t *pty, const char *name) {
  upty_shared_t *sh;
  int fd;

  if((fd=shm_open(name, O_RDWR, 0600)) < 0) {
    return -1;
  }

  sh = mmap(0, sizeof(*sh), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  if(sh == MAP_FAILED) {
    close(fd);
    return -1;
  }

  if(sh->magic != UPTY_MAGIC) {
    munmap(sh, sizeof(*sh));
    close(fd);
    return -1;
  }

  pty->sh = sh;
  pty->shm_fd = fd;
  snprintf(pty->shm_name, sizeof(pty->shm_name), "%s", name);

  return 0;
}


static void
upty_to_slave(void *ctx, const void *buf, size_t len) {
  upty_t *pty = (upty_t*)ctx;

  write(pty->sfd, buf, len);
}


static void
upty_to_remote(void *ctx, const void *buf, size_t len) {
  upty_t *pty = (upty_t*)ctx;

  write(pty->mfd, buf, len);
}


static void
upty_do_signal(void *ctx, int sig) {
  __upty_signal((upty_t*)ctx, sig);
}


static void
upty_do_eof(void *ctx) {
  upty_t *pty = (upty_t*)ctx;

  shutdown(pty->sfd, SHUT_WR);
}


static const ld_ops_t upty_ld_ops = {
  .to_slave  = upty_to_slave,
  .to_remote = upty_to_remote,
  .signal    = upty_do_signal,
  .eof       = upty_do_eof,
};


static void*
upty_pump(void *ctx) {
  unsigned char buf[1024];
  upty_t *pty = (upty_t*)ctx;
  struct pollfd pfd[2];
  unsigned int gen;
  ssize_t len;

  gen = __upty_gen(pty);

  while(pty->pump_run) {
    memset(pfd, 0, sizeof(pfd));
    pfd[0].fd = pty->mfd;
    pfd[0].events = POLLIN;
    pfd[1].fd = pty->sfd;
    pfd[1].events = POLLIN;

    if(poll(pfd, 2, UPTY_POLL_MS) < 0) {
      if(errno == EINTR) {
	continue;
      }
      break;
    }

    if(__upty_gen(pty) != gen) {
      gen = __upty_gen(pty);
      ld_termios_changed(&pty->ld);
    }

    if(pfd[0].revents & POLLIN) {
      if((len=read(pty->mfd, buf, sizeof(buf))) <= 0) {
	break;
      }
      ld_input(&pty->ld, buf, len);
    }

    if(pfd[1].revents & POLLIN) {
      if((len=read(pty->sfd, buf, sizeof(buf))) <= 0) {
	break;
      }
      ld_output(&pty->ld, buf, len);
    }

    if((pfd[0].revents | pfd[1].revents) & (POLLERR | POLLHUP | POLLNVAL)) {
      break;
    }
  }

  return 0;
}


static void
upty_export(upty_t *pty, int peer_fd) {
  char buf[96];

  if(pty->shm_fd >= 0 && pty->shm_name[0]) {
    snprintf(buf, sizeof(buf), "shm:%s:%d,%d,%d", pty->shm_name,
	     STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO);
    setenv("UPTY", buf, 1);
    unsetenv("UPTY_FD");
    return;
  }

  snprintf(buf, sizeof(buf), "fd:%d:%d,%d,%d", UPTY_CTL_FILENO,
	   STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO);
  setenv("UPTY", buf, 1);

  snprintf(buf, sizeof(buf), "%d", peer_fd);
  setenv("UPTY_FD", buf, 1);
}


upty_t*
__upty_create(int mfd, int sfd) {
  int ctl[2] = {-1, -1};
  upty_t *pty;

  spin_lock(&g_lock);

  if(!(pty=upty_alloc_locked())) {
    spin_unlock(&g_lock);
    return 0;
  }

  pty->mfd = mfd;
  pty->sfd = sfd;

  if(upty_shm_create(pty)) {
    if(!socketpair(AF_UNIX, SOCK_STREAM, 0, ctl)) {
      pty->ctl_fd = ctl[0];
    }
  }

  spin_unlock(&g_lock);

  upty_export(pty, ctl[1]);

  ld_init(&pty->ld, pty, &upty_ld_ops, pty);

  pty->pump_run = 1;
  if(pthread_create(&pty->pump, 0, upty_pump, pty)) {
    pty->pump_run = 0;
    __upty_destroy(pty);
    return 0;
  }

  return pty;
}


void
__upty_destroy(upty_t *pty) {
  if(!pty || !pty->used) {
    return;
  }

  if(pty->pump_run) {
    pty->pump_run = 0;
    pthread_join(pty->pump, 0);
  }

  spin_lock(&g_lock);

  for(int i=0; i<UPTY_MAX_FDS; i++) {
    if(g_fds[i].pty == pty) {
      g_fds[i].pty = 0;
      g_fds[i].fd = -1;
    }
  }

  if(pty->shm_fd >= 0) {
    munmap(pty->sh, sizeof(upty_shared_t));
    close(pty->shm_fd);
    if(pty->shm_name[0]) {
      shm_unlink(pty->shm_name);
    }
  }

  if(pty->ctl_fd >= 0) {
    close(pty->ctl_fd);
  }

  pty->sh = &pty->priv;
  pty->used = 0;

  spin_unlock(&g_lock);
}


unsigned int
__upty_gen(upty_t *pty) {
  unsigned int gen;

  upty_state_lock(pty);
  gen = pty->sh->gen;
  upty_state_unlock(pty);

  return gen;
}


void
__upty_signal(upty_t *pty, int sig) {
  pid_t pgrp;

  upty_state_lock(pty);
  pgrp = (pid_t)pty->sh->pgrp;
  upty_state_unlock(pty);

  if(pgrp <= 0) {
    return;
  }

  if(killpg(pgrp, sig) < 0) {
    kill(pgrp, sig);
  }
}


static void
upty_env_init_locked(void) {
  char buf[96], *s, *end, *key;
  upty_t *pty = 0;
  int is_shm;
  long fd;

  if(g_env_done) {
    return;
  }
  g_env_done = 1;

  if(!(s=getenv("UPTY"))) {
    return;
  }

  snprintf(buf, sizeof(buf), "%s", s);
  s = buf;

  if(!strncmp(s, "shm:", 4)) {
    is_shm = 1;
    s += 4;
  } else if(!strncmp(s, "fd:", 3)) {
    is_shm = 0;
    s += 3;
  } else {
    return;
  }

  if(!(end=strchr(s, ':'))) {
    return;
  }

  *end = 0;
  key = s;
  s = end + 1;

  while(*s) {
    fd = strtol(s, &end, 10);
    if(end == s) {
      break;
    }
    s = (*end == ',') ? end + 1 : end;

    if(upty_lookup_locked((int)fd)) {
      break;
    }

    if(!pty) {
      if(!(pty=upty_alloc_locked())) {
	break;
      }
      if(is_shm) {
	if(upty_shm_attach(pty, key)) {
	  pty->used = 0;
	  break;
	}
      } else {
	pty->ctl_fd = atoi(key);
	upty_mirror_in(pty);
      }
    }

    upty_bind_locked(pty, (int)fd);
  }
}


upty_t*
upty_attach(int fd) {
  upty_t *pty;

  if(fd < 0) {
    errno = EBADF;
    return 0;
  }

  spin_lock(&g_lock);

  if(!(pty=upty_alloc_locked())) {
    spin_unlock(&g_lock);
    return 0;
  }

  if(upty_bind_locked(pty, fd)) {
    pty->used = 0;
    spin_unlock(&g_lock);
    return 0;
  }

  spin_unlock(&g_lock);

  return pty;
}


int
upty_attach_fd(upty_t *pty, int fd) {
  int rc;

  if(!pty || fd < 0) {
    errno = EBADF;
    return -1;
  }

  spin_lock(&g_lock);
  rc = upty_bind_locked(pty, fd);
  spin_unlock(&g_lock);

  return rc;
}


int
upty_detach(int fd) {
  upty_t *pty = 0;

  spin_lock(&g_lock);

  for(int i=0; i<UPTY_MAX_FDS; i++) {
    if(g_fds[i].pty && g_fds[i].fd == fd) {
      pty = g_fds[i].pty;
      g_fds[i].pty = 0;
      g_fds[i].fd = -1;
    }
  }

  spin_unlock(&g_lock);

  if(!pty) {
    errno = ENOTTY;
    return -1;
  }

  return 0;
}


upty_t*
upty_lookup(int fd) {
  upty_t *pty;

  spin_lock(&g_lock);
  upty_env_init_locked();
  pty = upty_lookup_locked(fd);
  spin_unlock(&g_lock);

  return pty;
}


int
upty_index(const upty_t *pty) {
  return pty ? (int)(pty - g_pty) : -1;
}


void
upty_get_termios(upty_t *pty, struct termios *tio) {
  upty_state_lock(pty);
  *tio = pty->sh->tio;
  upty_state_unlock(pty);
}


void
upty_set_termios(upty_t *pty, const struct termios *tio) {
  upty_state_lock(pty);
  pty->sh->tio = *tio;
  upty_publish(pty);
  upty_state_unlock(pty);
}


void
upty_get_winsize(upty_t *pty, struct winsize *ws) {
  upty_state_lock(pty);
  *ws = pty->sh->ws;
  upty_state_unlock(pty);
}


void
upty_set_winsize(upty_t *pty, const struct winsize *ws) {
  upty_state_lock(pty);
  pty->sh->ws = *ws;
  upty_publish(pty);
  upty_state_unlock(pty);
}


pid_t
upty_get_pgrp(upty_t *pty) {
  pid_t pgrp;

  upty_state_lock(pty);
  pgrp = (pid_t)pty->sh->pgrp;
  upty_state_unlock(pty);

  return pgrp;
}


void
upty_set_pgrp(upty_t *pty, pid_t pgrp) {
  upty_state_lock(pty);
  pty->sh->pgrp = (int)pgrp;
  upty_publish(pty);
  upty_state_unlock(pty);
}


static int
upty_ioctl_locked(upty_t *pty, unsigned long request, void *argp) {
  switch(request) {
  case TIOCGETA:
    memcpy(argp, &pty->sh->tio, sizeof(struct termios));
    return 0;

  case TIOCSETA:
  case TIOCSETAW:
  case TIOCSETAF:
    memcpy(&pty->sh->tio, argp, sizeof(struct termios));
    upty_publish(pty);
    return 0;

  case TIOCGWINSZ:
    memcpy(argp, &pty->sh->ws, sizeof(struct winsize));
    return 0;

  case TIOCSWINSZ:
    memcpy(&pty->sh->ws, argp, sizeof(struct winsize));
    upty_publish(pty);
    return 0;

  case TIOCGPGRP:
    *(int*)argp = pty->sh->pgrp;
    return 0;

  case TIOCSPGRP:
    pty->sh->pgrp = *(int*)argp;
    upty_publish(pty);
    return 0;

  case TIOCGSID:
    *(int*)argp = pty->sh->sid;
    return 0;

  case TIOCSCTTY:
    pty->sh->sid = (int)getsid(0);
    upty_publish(pty);
    return 0;

  case TIOCNOTTY:
  case TIOCDRAIN:
  case TIOCFLUSH:
  case TIOCSTART:
  case TIOCSTOP:
  case TIOCSBRK:
  case TIOCCBRK:
  case TIOCEXCL:
  case TIOCNXCL:
    return 0;

  case TIOCOUTQ:
    *(int*)argp = 0;
    return 0;

  default:
    errno = ENOTTY;
    return -1;
  }
}


int
__upty_ioctl(int fd, unsigned long request, void *argp) {
  upty_t *pty;
  int rc;

  if(!(pty=upty_lookup(fd))) {
    return _ioctl(fd, request, argp);
  }

  upty_state_lock(pty);
  rc = upty_ioctl_locked(pty, request, argp);
  upty_state_unlock(pty);

  return rc;
}


int
ioctl(int fd, unsigned long request, ...) {
  va_list ap;
  void *argp;

  va_start(ap, request);
  argp = va_arg(ap, void*);
  va_end(ap);

  return __upty_ioctl(fd, request, argp);
}
