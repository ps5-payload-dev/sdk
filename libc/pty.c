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
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <termios.h>
#include <unistd.h>

#include "upty.h"


#define PTY_MAX 8


int _open(const char *path, int flags, ...);


static struct {
  int     master;
  int     slave;
  upty_t *pty;
} g_pairs[PTY_MAX];


static int
pty_remember(int master, int slave, upty_t *pty) {
  for(int i=0; i<PTY_MAX; i++) {
    if(!g_pairs[i].pty) {
      g_pairs[i].master = master;
      g_pairs[i].slave = slave;
      g_pairs[i].pty = pty;
      return 0;
    }
  }

  errno = ENOSPC;
  return -1;
}


static int
pty_find(int master) {
  for(int i=0; i<PTY_MAX; i++) {
    if(g_pairs[i].pty && g_pairs[i].master == master) {
      return i;
    }
  }

  return -1;
}


static int
pty_pair(int *amaster, int *aslave, upty_t **apty) {
  int x[2], y[2];
  upty_t *pty;

  if(socketpair(AF_UNIX, SOCK_STREAM, 0, x) < 0) {
    return -1;
  }

  if(socketpair(AF_UNIX, SOCK_STREAM, 0, y) < 0) {
    close(x[0]);
    close(x[1]);
    return -1;
  }

  if(!(pty=__upty_create(x[1], y[0]))) {
    close(x[0]);
    close(x[1]);
    close(y[0]);
    close(y[1]);
    return -1;
  }

  upty_attach_fd(pty, x[0]);
  upty_attach_fd(pty, y[1]);

  *amaster = x[0];
  *aslave = y[1];
  *apty = pty;

  return 0;
}


int
openpty(int *amaster, int *aslave, char *name, const struct termios *tio,
	const struct winsize *ws) {
  upty_t *pty;
  int master;
  int slave;

  if(pty_pair(&master, &slave, &pty)) {
    return -1;
  }

  if(tio) {
    upty_set_termios(pty, tio);
  }
  if(ws) {
    upty_set_winsize(pty, ws);
  }

  if(pty_remember(master, slave, pty)) {
    __upty_destroy(pty);
    close(master);
    close(slave);
    return -1;
  }

  if(name) {
    sprintf(name, "/dev/upts/%d", upty_index(pty));
  }

  *amaster = master;
  *aslave = slave;

  return 0;
}


int
posix_openpt(int flags) {
  upty_t *pty;
  int master;
  int slave;

  if(flags & ~(O_RDWR | O_NOCTTY | O_CLOEXEC)) {
    errno = EINVAL;
    return -1;
  }

  if(pty_pair(&master, &slave, &pty)) {
    return -1;
  }

  if(pty_remember(master, slave, pty)) {
    __upty_destroy(pty);
    close(master);
    close(slave);
    return -1;
  }

  if(flags & O_CLOEXEC) {
    fcntl(master, F_SETFD, FD_CLOEXEC);
  }

  return master;
}


char*
ptsname(int master) {
  static char buf[32];
  int i;

  if((i=pty_find(master)) < 0) {
    errno = ENOTTY;
    return 0;
  }

  snprintf(buf, sizeof(buf), "/dev/upts/%d", upty_index(g_pairs[i].pty));

  return buf;
}


int
grantpt(int master) {
  if(pty_find(master) < 0) {
    errno = ENOTTY;
    return -1;
  }

  return 0;
}


int
unlockpt(int master) {
  if(pty_find(master) < 0) {
    errno = ENOTTY;
    return -1;
  }

  return 0;
}


static int
pty_dup(upty_t *pty, int fd) {
  int nfd;

  if((nfd=dup(fd)) < 0) {
    return -1;
  }

  if(upty_attach_fd(pty, nfd)) {
    close(nfd);
    return -1;
  }

  return nfd;
}


int
open(const char *path, int flags, ...) {
  mode_t mode = 0;
  va_list ap;
  upty_t *pty;

  if(path && !strcmp(path, "/dev/tty")) {
    if((pty=upty_lookup(STDIN_FILENO))) {
      return pty_dup(pty, STDIN_FILENO);
    }
  }

  if(path && !strncmp(path, "/dev/upts/", 10)) {
    int idx = atoi(path + 10);

    for(int i=0; i<PTY_MAX; i++) {
      if(g_pairs[i].pty && upty_index(g_pairs[i].pty) == idx) {
	return pty_dup(g_pairs[i].pty, g_pairs[i].slave);
      }
    }

    errno = ENOENT;
    return -1;
  }

  if(flags & O_CREAT) {
    va_start(ap, flags);
    mode = (mode_t)va_arg(ap, int);
    va_end(ap);
  }

  return _open(path, flags, mode);
}


int
login_tty(int fd) {
  upty_t *pty = upty_lookup(fd);

  setsid();

  if(dup2(fd, STDIN_FILENO) < 0 ||
     dup2(fd, STDOUT_FILENO) < 0 ||
     dup2(fd, STDERR_FILENO) < 0) {
    return -1;
  }

  if(pty) {
    upty_attach_fd(pty, STDIN_FILENO);
    upty_attach_fd(pty, STDOUT_FILENO);
    upty_attach_fd(pty, STDERR_FILENO);
    upty_set_pgrp(pty, getpgrp());
  }

  if(fd > STDERR_FILENO) {
    close(fd);
  }

  return 0;
}
