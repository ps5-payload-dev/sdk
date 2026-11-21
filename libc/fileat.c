/* Copyright (C) 2026 PristMC

This program is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 3, or (at your option) any
later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; see the file COPYING. If not, see
<http://www.gnu.org/licenses/>.  */

/*
 * File system syscalls that libkernel does not export. Like mount.c, they
 * check the carry flag and set errno, so a failure returns -1 instead of the
 * positive errno value (openat() on a missing path used to return 2).
 */

#include <errno.h>
#include <fcntl.h>
#include <stdarg.h>
#include <unistd.h>

#include <sys/mount.h>
#include <sys/stat.h>
#include <sys/syscall.h>


static long
__syscall6(long n, long a1, long a2, long a3, long a4, long a5, long a6) {
  unsigned long ret;
  char iserror;

  register long r10 __asm__("r10") = a4;
  register long r8 __asm__("r8") = a5;
  register long r9 __asm__("r9") = a6;

  __asm__ __volatile__(
     "syscall" : "=a"(ret), "=@ccc"(iserror), "+r"(r10), "+r"(r8), "+r"(r9) :
     "a"(n), "D"(a1), "S"(a2), "d"(a3) :
     "rcx", "r11", "memory"
     );

  return iserror ? -ret : ret;
}


static long
__check(long ret) {
  if(ret < 0) {
    errno = -ret;
    return -1;
  }

  return ret;
}


int
link(const char *path, const char *link) {
  return __check(__syscall6(SYS_link, (long)path, (long)link, 0, 0, 0, 0));
}


int
dup(int fd) {
  return __check(__syscall6(SYS_dup, fd, 0, 0, 0, 0, 0));
}


int
getfsstat(struct statfs *buf, long bufsize, int mode) {
  return __check(__syscall6(SYS_getfsstat, (long)buf, bufsize, mode, 0, 0, 0));
}


int
statfs(const char *path, struct statfs *buf) {
  return __check(__syscall6(SYS_statfs, (long)path, (long)buf, 0, 0, 0, 0));
}


int
fstatfs(int fd, struct statfs *buf) {
  return __check(__syscall6(SYS_fstatfs, fd, (long)buf, 0, 0, 0, 0));
}


int
fstatat(int fd, const char *path, struct stat *sb, int flag) {
  return __check(__syscall6(SYS_fstatat, fd, (long)path, (long)sb, flag, 0, 0));
}


int
linkat(int fd1, const char *path1, int fd2, const char *path2, int flag) {
  return __check(__syscall6(SYS_linkat, fd1, (long)path1, fd2, (long)path2,
                            flag, 0));
}


int
mkdirat(int fd, const char *path, mode_t mode) {
  return __check(__syscall6(SYS_mkdirat, fd, (long)path, mode, 0, 0, 0));
}


int
openat(int fd, const char *path, int flags, ...) {
  int mode = 0;

  if(flags & O_CREAT) {
    va_list ap;
    va_start(ap, flags);
    mode = va_arg(ap, int);
    va_end(ap);
  }

  return __check(__syscall6(SYS_openat, fd, (long)path, flags, mode, 0, 0));
}


ssize_t
readlinkat(int fd, const char *path, char *buf, size_t bufsize) {
  return __check(__syscall6(SYS_readlinkat, fd, (long)path, (long)buf, bufsize,
                            0, 0));
}


int
renameat(int fromfd, const char *from, int tofd, const char *to) {
  return __check(__syscall6(SYS_renameat, fromfd, (long)from, tofd, (long)to,
                            0, 0));
}


int
symlinkat(const char *path1, int fd, const char *path2) {
  return __check(__syscall6(SYS_symlinkat, (long)path1, fd, (long)path2, 0, 0, 0));
}


int
unlinkat(int fd, const char *path, int flag) {
  return __check(__syscall6(SYS_unlinkat, fd, (long)path, flag, 0, 0, 0));
}


int
futimens(int fd, const struct timespec times[2]) {
  return __check(__syscall6(SYS_futimens, fd, (long)times, 0, 0, 0, 0));
}
