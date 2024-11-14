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
#include "rtld.h"


/**
 * Dependencies to standard libraries.
 **/
static char* (*strdup)(const char*) = 0;
static int (*strcmp)(const char*, const char*) = 0;
static int (*strncmp)(const char*, const char*, unsigned long) = 0;
static unsigned long (*strlen)(const char*) = 0;

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
 * Declare init/fini functions for the different runtime loaders.
 **/
int __rtld_so_init(void);
int __rtld_sprx_init(void);
int __rtld_payload_init(void);
int __rtld_payload_fini(void);


/**
 * Declare constructors for the different type of libs.
 **/
rtld_lib_t* __rtld_sprx_new(rtld_lib_t* prev, const char* soname);
rtld_lib_t* __rtld_so_new(rtld_lib_t* prev, const char* soname);


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


static int
ref_open(rtld_lib_t* ctx) {
  return 0;
}


static void*
ref_sym(rtld_lib_t* ctx, const char* name) {
  rtld_ref_lib_t* lib = (rtld_ref_lib_t*)ctx;
  return __rtld_lib_sym(lib->ref, name);
}


static int
ref_close(rtld_lib_t* ctx) {
  return 0;
}


static void
ref_destroy(rtld_lib_t* ctx) {
  free(ctx->soname);
  free(ctx);
}


rtld_lib_t*
__rtld_lib_new(rtld_lib_t* prev, const char* soname) {
  rtld_ref_lib_t* lib = 0;
  rtld_lib_t* ref = 0;

  while(prev && prev->prev) {
    prev = prev->prev;
  }

  for(ref=prev; ref; ref=ref->next) {
    if(!strcmp(ref->soname, soname)) {
      lib = calloc(1, sizeof(rtld_ref_lib_t));
      lib->soname  = strdup(soname);
      lib->prev    = prev;
      lib->ref     = ref;
      lib->open    = ref_open;
      lib->sym     = ref_sym;
      lib->close   = ref_close;
      lib->destroy = ref_destroy;

      return (rtld_lib_t*)lib;
    }
  }

  if(endswith(soname, ".sprx")) {
    return __rtld_sprx_new(prev, soname);
  } else {
    return __rtld_so_new(prev, soname);
  }
}


int
__rtld_lib_open(rtld_lib_t* ctx) {
  return ctx->open(ctx);
}


void*
__rtld_lib_sym(rtld_lib_t* ctx, const char* name) {
  return ctx->sym(ctx, name);
}


int
__rtld_lib_close(rtld_lib_t* ctx) {
  int err;

  if(ctx->next && (err=__rtld_lib_close(ctx->next))) {
    return err;
  }

  return ctx->close(ctx);
}


void
__rtld_lib_destroy(rtld_lib_t* ctx) {
  if(ctx->next) {
    __rtld_lib_destroy(ctx->next);
  }

  ctx->destroy(ctx);
}


int
__rtld_init(void) {
  int err;

  if(!KERNEL_DLSYM(0x2, strdup)) {
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
  if(!KERNEL_DLSYM(0x2, calloc)) {
    return -1;
  }
  if(!KERNEL_DLSYM(0x2, free)) {
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
