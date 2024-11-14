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

#include <dlfcn.h>
#include <sys/errno.h>


/**
 * See crt/rtld.h.
 **/
struct rtld_lib;
typedef struct rtld_lib rtld_lib_t;

rtld_lib_t* __rtld_lib_new(rtld_lib_t* prev, const char* soname);
int __rtld_lib_open(rtld_lib_t* ctx);
void* __rtld_lib_sym(rtld_lib_t* ctx, const char* name);
int __rtld_lib_close(rtld_lib_t* ctx);
void __rtld_lib_destroy(rtld_lib_t* ctx);


char* _Strerror(int, char*);
static int g_dlerrno = 0;


void*
dlopen(const char *filename, int flags) {
  rtld_lib_t* lib;

  if(!(flags & RTLD_MODEMASK)) {
    g_dlerrno = EINVAL;
    return 0;
  }
  if(flags & RTLD_TRACE) {
    g_dlerrno = ENOSYS;
    return 0;
  }
  if(flags & RTLD_NOW) {
    g_dlerrno = ENOSYS;
    return 0;
  }
  if(flags & RTLD_GLOBAL) {
    g_dlerrno = ENOSYS;
    return 0;
  }

  if(!(lib=__rtld_lib_new(0, filename))) {
    g_dlerrno = ENOMEM;
    return 0;
  }
  if((g_dlerrno=__rtld_lib_open(lib))) {
    __rtld_lib_destroy(lib);
    return 0;
  }

  g_dlerrno = 0;
  return lib;
}


void*
dlsym(void *handle, const char *symbol) {
  void* addr;

  if(handle == 0) {
    g_dlerrno = ENOSYS;
    return 0;
  }
  if(handle == RTLD_DEFAULT) {
    g_dlerrno = ENOSYS;
    return 0;
  }
  if(handle == RTLD_NEXT) {
    g_dlerrno = ENOSYS;
    return 0;
  }
  if(handle == RTLD_SELF) {
    g_dlerrno = ENOSYS;
    return 0;
  }

  if(!(addr=__rtld_lib_sym(handle, symbol))) {
    g_dlerrno = EINVAL;
    return 0;
  }

  g_dlerrno = 0;
  return addr;
}


int
dlclose(void *handle) {
  if(!(g_dlerrno=__rtld_lib_close(handle))) {
    __rtld_lib_destroy(handle);
  }

  return g_dlerrno;
}


char*
dlerror(void) {
  if(g_dlerrno) {
    return _Strerror(g_dlerrno, 0);
  }

  return 0;
}
