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
#include "syscall.h"
#include "rtld.h"
#include "rtld_payload.h"
#include "rtld_so.h"
#include "rtld_sprx.h"


/**
 * Dependencies to standard libraries.
 **/
static char* (*strcpy)(char*, const char*) = 0;
static int (*strcmp)(const char*, const char*) = 0;
static int (*strncmp)(const char*, const char*, unsigned long) = 0;
static unsigned long (*strlen)(const char*) = 0;
static char* (*strcat)(char*, const char*) = 0;
static int (*sprintf)(char*, const char*, ...) = 0;

static char* (*getenv)(const char*) = 0;
static char* (*getcwd)(char*, unsigned long) = 0;

static void* (*calloc)(unsigned long, unsigned long) = 0;
static void (*free)(void*) = 0;


/**
 * Extend the rtld_lib_t type with auxiliary parameters for shallow
 * copies of a lib. This requires -fms-extensions.
 **/
typedef struct rtld_ref_lib {
  struct rtld_lib;

  rtld_lib_t* ref;
} rtld_ref_lib_t;


/**
 * Check if a string ends with a given suffix.
 **/
static int
endswith(const char *string, const char* suffix) {
  unsigned long suffix_len = strlen(suffix);
  unsigned long string_len = strlen(string);

  if(string_len < suffix_len) {
    return 0;
  }

  return strncmp(string + string_len - suffix_len,
                 suffix, suffix_len) == 0;
}


/**
 *
 **/
static int
ref_open(rtld_lib_t* ctx) {
  rtld_ref_lib_t* lib = (rtld_ref_lib_t*)ctx;
  return __rtld_lib_open(lib->ref);
}


/**
 *
 **/
static void*
ref_sym2addr(rtld_lib_t* ctx, const char* name) {
  rtld_ref_lib_t* lib = (rtld_ref_lib_t*)ctx;
  return __rtld_lib_sym2addr(lib->ref, name);
}


/**
 *
 **/
static const char*
ref_addr2sym(rtld_lib_t* ctx, void* addr) {
  rtld_ref_lib_t* lib = (rtld_ref_lib_t*)ctx;
  return __rtld_lib_addr2sym(lib->ref, addr);
}


/**
 *
 **/
static int
ref_close(rtld_lib_t* ctx) {
  rtld_ref_lib_t* lib = (rtld_ref_lib_t*)ctx;
  return __rtld_lib_close(lib->ref);
}


/**
 *
 **/
static void
ref_destroy(rtld_lib_t* ctx) {
  free(ctx);
}


int
__rtld_find_file(const char *name, char* path) {
  unsigned long off = 0;
  const char *ldpaths;
  char buf[0x100];
  char cwd[1024];
  int err = 0;

  if(!name || !*name || !path) {
    return -1;
  }

  path[0] = 0;
  if(name[0] == '/') {
    if(!(err=__syscall(SYS_stat, name, buf))) {
      strcpy(path, name);
    }
    return err;
  }

  if(getcwd(cwd, sizeof(cwd))) {
    strcpy(path, cwd);
    strcat(path, "/");
    strcat(path, name);
    if(!__syscall(SYS_stat, path, buf)) {
      return 0;
    }
  }

  sprintf(path, "/system/priv/lib/%s", name);
  if(!__syscall(SYS_access, path, 0)) {
    return 0;
  }

  sprintf(path, "/system/common/lib/%s", name);
  if(!__syscall(SYS_access, path, 0)) {
    return 0;
  }

  sprintf(path, "/system_ex/priv_ex/lib/%s", name);
  if(!__syscall(SYS_access, path, 0)) {
    return 0;
  }

  sprintf(path, "/system_ex/common_ex/lib/%s", name);
  if(!__syscall(SYS_access, path, 0)) {
    return 0;
  }

  if((ldpaths=getenv("LD_LIBRARY_PATH"))) {
    for(int i=0; ldpaths[i]; i++) {
      path[off++] = ldpaths[i];
      if(path[off] == ':' || ldpaths[i+1] == 0) {
	path[off] = '/';
	path[off+1] = 0;
	strcat(path, name);
	off = 0;
	if(!__syscall(SYS_stat, path, buf)) {
	  return 0;
	}
      }
    }
  }

  strcpy(path, "/user/homebrew/lib/");
  strcat(path, name);
    if(!__syscall(SYS_access, path, 0)) {
      return 0;
    }

  path[0] = 0;
  return -1;
}


rtld_lib_t*
__rtld_lib_new(rtld_lib_t* prev, const char* soname) {
  rtld_lib_t* first = prev;
  rtld_ref_lib_t* lib = 0;
  rtld_lib_t* ref = 0;
  char path[1024];

  // find the first lib in the linked list
  while(first->prev) {
    first = first->prev;
  }

  if(__rtld_find_file(soname, path)) {
    strcpy(path, soname);
  }

  // check if the lib is already loaded
  for(ref=first; ref; ref=ref->next) {
    if(!strcmp(ref->soname, path)) {
      lib = calloc(1, sizeof(rtld_ref_lib_t));
      lib->prev     = prev;
      lib->ref      = ref;
      lib->open     = ref_open;
      lib->sym2addr = ref_sym2addr;
      lib->addr2sym = ref_addr2sym;
      lib->close    = ref_close;
      lib->destroy  = ref_destroy;
      lib->refcnt   = 0;
      lib->mapbase  = ref->mapbase;
      lib->mapsize  = ref->mapsize;

      strcpy(lib->soname, ref->soname);

      return (rtld_lib_t*)lib;
    }
  }

  // .sprx and .so files have different loaders
  if(endswith(soname, ".sprx")) {
    return __rtld_sprx_new(prev, soname);
  } else {
    return __rtld_so_new(prev, soname);
  }
}


int
__rtld_lib_open(rtld_lib_t* ctx) {
  ctx->refcnt++;
  if(ctx->refcnt == 1) {
    return ctx->open(ctx);
  }
  return 0;
}


void*
__rtld_lib_sym2addr(rtld_lib_t* ctx, const char* name) {
  if(name) {
    return ctx->sym2addr(ctx, name);
  } else {
    return 0;
  }
}


const char*
__rtld_lib_addr2sym(rtld_lib_t* ctx, void* addr) {
  if(addr) {
    return ctx->addr2sym(ctx, addr);
  } else {
    return 0;
  }
}


int
__rtld_lib_close(rtld_lib_t* ctx) {
  int err;

  ctx->refcnt--;
  if(ctx->refcnt > 0) {
    return 0;
  }

  if(ctx->next && (err=__rtld_lib_close(ctx->next))) {
    return err;
  }
  if(ctx->prev) {
    ctx->prev->next = 0;
  }

  if(!(err=ctx->close(ctx))) {
    __rtld_lib_destroy(ctx);
  }

  return err;
}


void
__rtld_lib_destroy(rtld_lib_t* ctx) {
  ctx->destroy(ctx);
}


int
__rtld_init(void) {
  int err;

  if(!KERNEL_DLSYM(0x2, strcpy)) {
    return -1;
  }
  if(!KERNEL_DLSYM(0x2, strcat)) {
    return -1;
  }
  if(!KERNEL_DLSYM(0x2, strcmp)) {
    return -1;
  }
  if(!KERNEL_DLSYM(0x2, strncmp)) {
    return -1;
  }
  if(!KERNEL_DLSYM(0x2, strlen)) {
    return -1;
  }
  if(!KERNEL_DLSYM(0x2, sprintf)) {
    return -1;
  }
  if(!KERNEL_DLSYM(0x2, calloc)) {
    return -1;
  }
  if(!KERNEL_DLSYM(0x2, free)) {
    return -1;
  }
  if(!KERNEL_DLSYM(0x2, getenv)) {
    return -1;
  }
  if(!KERNEL_DLSYM(0x2, getcwd)) {
    return -1;
  }

  if((err=__rtld_sprx_init())) {
    return err;
  }
  if((err=__rtld_so_init())) {
    return err;
  }
  if((err=__rtld_payload_init())) {
    return err;
  }

  return 0;
}


int
__rtld_fini(void) {
  return __rtld_payload_fini();
}
