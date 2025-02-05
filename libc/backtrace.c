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

#include <dlfcn.h>
#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#define MAX_SYMBOL_SIZE 99


size_t
backtrace(void **buffer, size_t size) {
  void **frame = __builtin_frame_address(0);
  void *addr = __builtin_return_address(0);
  int i;

  for(i=0; i<size && frame; i++) {
    buffer[i] = addr;
    frame = (void**)*frame;

    if(frame) {
      addr = *(frame+1);
    } else {
      break;
    }
  }

  return i;
}


char**
backtrace_symbols(void *const *buffer, size_t size) {
  void* mem = malloc(size*sizeof(char*) + size*MAX_SYMBOL_SIZE);
  char *strbuf = mem + (size*sizeof(char*));
  char **symbols = mem;
  Dl_info dli;

  if(!mem) {
    return NULL;
  }

  for(int i=0; i<size; i++) {
    void* addr = buffer[i];
    symbols[i] = strbuf + (i*MAX_SYMBOL_SIZE);

    if(!dladdr(addr, &dli)) {
      snprintf(symbols[i], MAX_SYMBOL_SIZE, "? [0x%p]", addr);

    } else if(!dli.dli_sname) {
      snprintf(symbols[i], MAX_SYMBOL_SIZE, "%s(+0x%p) [0x%p]",
               dli.dli_fname,
               (void*)(addr - dli.dli_fbase),
               addr);

    } else {
      snprintf(symbols[i], MAX_SYMBOL_SIZE, "%s(%s+0x%p) [0x%p]",
               dli.dli_fname,
               dli.dli_sname,
               (void*)(addr - dli.dli_fbase),
               addr);
    }
  }

  return (char**)mem;
}


int
backtrace_symbols_fd(void *const* buffer, size_t size, int fd) {
  char sym[MAX_SYMBOL_SIZE+1];
  Dl_info dli;

  for(int i=0; i<size; i++) {
    void* addr = buffer[i];

    if(!dladdr(addr, &dli)) {
      snprintf(sym, MAX_SYMBOL_SIZE, "? [0x%p]\n", addr);

    } else if(!dli.dli_sname) {
      snprintf(sym, MAX_SYMBOL_SIZE, "%s(+0x%p) [0x%p]\n",
               dli.dli_fname,
               (void*)(addr - dli.dli_fbase),
               addr);

    } else {
      snprintf(sym, MAX_SYMBOL_SIZE, "%s(%s+0x%p) [0x%p]\n",
               dli.dli_fname,
               dli.dli_sname,
               (void*)(addr - dli.dli_fbase),
               addr);
    }
    if(write(fd, sym, strlen(sym)) != strlen(sym)) {
      return -1;
    }
  }

  return 0;
}
