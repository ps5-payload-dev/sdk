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

#include <unistd.h>

#include <sys/mman.h>
#include <sys/syscall.h>

#include "../include/ps5/kernel.h"


int
mprotect(const void* addr, size_t size, int prot) {
  if((prot & PROT_EXEC)) {
    return kernel_mprotect(-1, (intptr_t)addr, size, prot);
  } else {
      return (int)__syscall(SYS_mprotect, addr, size, prot);
  }
}


void*
mmap(void* addr, size_t size, int prot, int flags, int fd, off_t offset) {
  void *mapped_addr;

  if(!(prot & PROT_EXEC)) {
    return (void*)__syscall(SYS_mmap, addr, size, prot, flags, fd, offset);
  }

  prot &= ~PROT_EXEC;
  mapped_addr = (void*)__syscall(SYS_mmap, addr, size, prot, flags, fd, offset);
  if(mapped_addr == MAP_FAILED) {
    return MAP_FAILED;
  }

  prot |= PROT_EXEC;
  if(kernel_mprotect(-1, (intptr_t)mapped_addr, size, prot)) {
    return MAP_FAILED;
  }

  return mapped_addr;
}
