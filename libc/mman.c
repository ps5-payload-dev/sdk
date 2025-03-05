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

#include <sys/mman.h>
#include <sys/syscall.h>


/**
 * shared objects do not link with crt1.o, declare deps as weak.
 **/
__attribute__((weak)) int kernel_mprotect(pid_t, intptr_t, size_t, int);


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


static void*
sys_mmap(void* addr, size_t size, int prot, int flags, int fd, off_t offset) {
  long ret;

  if((ret=__syscall6(SYS_mmap, (long)addr, size, prot, flags, fd, offset)) < 0) {
    errno = -ret;
    return (void*)-1;
  }

  return (void*)ret;
}


static int
sys_mprotect(const void* addr, size_t size, int prot) {
  long ret;

  if((ret=__syscall6(SYS_mprotect, (long)addr, size, prot, 0, 0, 0)) < 0) {
    errno = -ret;
    return -1;
  }

  return (int)ret;
}


int
mprotect(const void* addr, size_t size, int prot) {
  if((prot & PROT_EXEC)) {
    return kernel_mprotect(-1, (intptr_t)addr, size, prot);
  } else {
      return sys_mprotect(addr, size, prot);
  }
}


void*
mmap(void* addr, size_t size, int prot, int flags, int fd, off_t offset) {
  void *mapped_addr;

  if(!(prot & PROT_EXEC)) {
    return sys_mmap(addr, size, prot, flags, fd, offset);
  }

  prot &= ~PROT_EXEC;
  mapped_addr = sys_mmap(addr, size, prot, flags, fd, offset);
  if(mapped_addr == MAP_FAILED) {
    return MAP_FAILED;
  }

  prot |= PROT_EXEC;
  if(kernel_mprotect(-1, (intptr_t)mapped_addr, size, prot)) {
    return MAP_FAILED;
  }

  return mapped_addr;
}
