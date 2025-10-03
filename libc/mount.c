/* Copyright (C) 2025 John Törnblom

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
#include <unistd.h>

#include <sys/mount.h>
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


int
mount(const char *type, const char *dir, int flags, void *data) {
  long ret;

  if((ret=__syscall6(SYS_mount, (long)type, (long)dir, flags, (long)data, 0, 0)) < 0) {
    errno = -ret;
    return -1;
  }

  return 0;
}


int
nmount(struct iovec *iov, unsigned int niov, int flags) {
  long ret;

  if((ret=__syscall6(SYS_nmount, (long)iov, niov, flags, 0, 0, 0)) < 0) {
    errno = -ret;
    return -1;
  }

  return 0;
}


int
unmount(const char *dir, int flags) {
  long ret;

  if((ret=__syscall6(SYS_unmount, (long)dir, flags, 0, 0, 0, 0)) < 0) {
    errno = -ret;
    return -1;
  }

  return 0;
}

