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


/**
 * Implemented in ../crt/rtld_payload.c
 **/
__attribute__((weak)) void* __dlopen(const char*, int);
__attribute__((weak)) int   __dladdr(const void*, Dl_info*);
__attribute__((weak)) void* __dlsym(void*, const char*);
__attribute__((weak)) int   __dlclose(void*);
__attribute__((weak)) char* __dlerror(void);


void*
dlopen(const char *filename, int flags) {
  if(__dlopen) {
    return __dlopen(filename, flags);
  }
  return 0;
}


void*
dlsym(void *handle, const char *symbol) {
  if(__dlsym) {
    return __dlsym(handle, symbol);
  }
  return 0;
}


int
dladdr(const void *addr, Dl_info *info) {
  if(__dladdr) {
    return __dladdr(addr, info);
  }
  return 0;
}


int
dlclose(void *handle) {
  if(__dlclose) {
    return __dlclose(handle);
  }
  return -1;
}


char*
dlerror(void) {
  if(__dlerror) {
    return __dlerror();
  }

  return 0;
}
