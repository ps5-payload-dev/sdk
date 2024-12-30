/* Copyright (C) 2024 John Törnblom

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

#include "kernel.h"
#include "klog.h"
#include "payload.h"
#include "rtld_payload.h"


/**
 *
 **/
#define SA_SIGINFO 0x0040


/**
 *
 **/
typedef struct sigset {
  unsigned int bits[4];
} sigset_t;


/**
 *
 **/
union sigval {
  int sival_int;
  void *sival_ptr;
  int sigval_int;
  void *sigval_ptr;
};


/**
 *
 **/
typedef struct siginfo {
  int si_signo;
  int si_errno;
  int si_code;
  int si_pid;
  int si_uid;
  int si_status;
  void *si_addr;
  union sigval si_value;
  union	{
    struct {
      int _trapno;
    } _fault;
    struct {
      int _timerid;
      int _overrun;
    } _timer;
    struct {
      int _mqd;
    } _mesgq;
    struct {
      long _band;
    } _poll;
    struct {
      long __spare1__;
      int __spare2__[7];
    } __spare__;
  } _reason;
} siginfo_t;


/**
 *
 **/
struct sigaction {
  void (*sa_sigaction)(int, struct siginfo *, void *);
  int sa_flags;
  sigset_t sa_mask;
};


/**
 * Map of signals to install termination signal handler.
 **/
static unsigned char term_sigmap[] = {
  0, // NOSIG
  1, // SIGHUP
  1, // SIGINT
  1, // SIGQUIT
  0, // SIGILL
  1, // SIGTRAP
  1, // SIGABRT
  1, // SIGEMT
  1, // SIGFPE
  0, // SIGKILL
  1, // SIGBUS
  1, // SIGSEGV
  1, // SIGSYS
  1, // SIGPIPE
  1, // SIGALRM
  1, // SIGTERM
  0, // SIGURG
  0, // SIGSTOP
  0, // SIGTSTP
  0, // SIGCONT
  0, // SIGCHLD
  0, // SIGTTIN
  0, // SIGTTOU
  0, // SIGIO
  1, // SIGXCPU
  1, // SIGXFSZ
  1, // SIGVTALRM
  1, // SIGPROF
  0, // SIGWINCH
  0, // SIGINFO
  1, // SIGUSR1
  1, // SIGUSR2
};


/**
 * Remember the default signal handlers.
 **/
static struct sigaction default_sigmap[sizeof(term_sigmap)];


/**
 * Dependencies to libkernel
 **/
static int (*sigaction)(int, const struct sigaction*, struct sigaction *) = 0;
static int (*sigemptyset)(sigset_t*) = 0;


/**
 * When recieving a termination signal, print a stacktrace to /dev/klog
 * and exit gracefully.
 **/
static void
on_term_signal(int sig, siginfo_t *info, void *context) {
  void **frame = __builtin_frame_address(0);
  void *addr = info->si_addr;
  unsigned long mapbase;
  unsigned int handle;
  char path[1024];
  Dl_info dli;
  int i = 0;

  // skip interupt frames
  if(frame) {
    frame = (void**)*frame;
  }
  if(frame) {
    frame = (void**)*frame;
  }

  klog_printf("Caught the POSIX signal %d:\n", sig);
  while(frame) {
    if(dladdr(addr, &dli)) {
      // Address is mapped by crt
      if(dli.dli_sname) {
        klog_printf("[%d] %s(%s+0x%lx)[0x%lx]\n", i, dli.dli_fname, dli.dli_sname,
                    (long)(addr - dli.dli_fbase), (long)addr);
      } else {
        klog_printf("[%d] %s(+0x%lx)[0x%lx]\n", i, dli.dli_fname,
                    (long)(addr - dli.dli_fbase), (long)addr);
      }
    } else if(!kernel_dynlib_find_handle(-1, (long)addr, &handle)) {
      // Address is mapped by the kernel
      mapbase = kernel_dynlib_mapbase_addr(-1, handle);
      kernel_dynlib_path(-1, handle, path, sizeof(path));
      klog_printf("[%d] %s(+0x%lx)[0x%lx]\n", i, path, addr - mapbase,
                  (long)addr);
    } else {
      // Address is mapped by payload
      klog_printf("[%d] ?[0x%lx]\n", i, (long)addr);
    }

    frame = (void**)*frame;
    if(frame) {
      addr = *(frame+1);
    }
    i++;
  }

  payload_exit(-sig);
}


/**
 * Assign custom signal handlers so we can do our own stacktrace.
 **/
int
__stacktrace_init(void) {
  struct sigaction sa = {
    .sa_flags = SA_SIGINFO,
    .sa_sigaction = on_term_signal
  };

  if(!KERNEL_DLSYM(0x1, sigaction)) {
    if(!KERNEL_DLSYM(0x2001, sigaction)) {
      klog_puts("Unable to resolve the symbol 'sigaction'");
      return -1;
    }
  }
  if(!KERNEL_DLSYM(0x1, sigemptyset)) {
    if(!KERNEL_DLSYM(0x2001, sigemptyset)) {
      klog_puts("Unable to resolve the symbol 'sigemptyset'");
      return -1;
    }
  }

  for(int signo=1; signo<sizeof(term_sigmap); signo++) {
    if(!term_sigmap[signo]) {
      continue;
    }
    if(sigemptyset(&sa.sa_mask)) {
      klog_perror("sigemptyset");
      return -1;
    }
    if(sigaction(signo, &sa, &default_sigmap[signo])) {
      klog_perror("sigaction");
      return -1;
    }
  }

  return 0;
}


/**
 * Restore signal handlers.
 **/
int
__stacktrace_fini(void) {
  for(int signo=1; signo<sizeof(term_sigmap); signo++) {
    if(!term_sigmap[signo]) {
      continue;
    }

    if(sigaction(signo, &default_sigmap[signo], 0)) {
      klog_perror("sigaction");
      return -1;
    }
  }

  return 0;
}
