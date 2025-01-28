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

#pragma once

#include "rtld.h"


/**
 * Define macros needed by dlopen() and dlsym().
 **/
#define RTLD_NEXT    ((void*)-1)
#define RTLD_DEFAULT ((void*)-2)
#define RTLD_SELF    ((void*)-3)

#define RTLD_LAZY     0x0001
#define RTLD_NOW      0x0002
#define RTLD_MODEMASK 0x0003
#define RTLD_GLOBAL   0x0100
#define RTLD_LOCAL    0x0000
#define RTLD_TRACE    0x0200
#define RTLD_NODELETE 0x1000
#define RTLD_NOLOAD   0x2000


/**
 * Define data structure needed by dladdr().
 **/
typedef struct dl_info {
  const char *dli_fname;
  void *dli_fbase;
  const char *dli_sname;
  void *dli_saddr;
} Dl_info;


/**
 * Declare prototypes for dynamic loading functions typically provided by libc.
 **/
void* dlopen(const char *filename, int flags);
int dladdr(void *addr, Dl_info *info);
void* dlsym(void *handle, const char *symbol);
int dlclose(void *handle);
char* dlerror(void);



/**
 * Create a new payload loader.
 **/
rtld_lib_t* __rtld_payload_new(void);


/**
 * Initialize so loader dependencies.
 **/
int __rtld_payload_init(void);
