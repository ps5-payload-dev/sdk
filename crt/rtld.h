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


/**
 * Prototypes for different kinds of libs (.sprx or .so).
 **/
typedef struct rtld_lib {
  int (*open)(struct rtld_lib* ctx);
  void* (*sym2addr)(struct rtld_lib* ctx, const char* name);
  const char* (*addr2sym)(struct rtld_lib* ctx, void* addr);
  int (*close)(struct rtld_lib* ctx);
  void (*destroy)(struct rtld_lib* ctx);

  char soname[1024];
  void *mapbase;
  unsigned long mapsize;
  int refcnt;
  struct rtld_lib* next;
  struct rtld_lib* prev;
} rtld_lib_t;


/**
 * Allocate a new lib object with the given soname.
 **/
rtld_lib_t* __rtld_lib_new(rtld_lib_t* prev, const char* soname);


/**
 * Open a lib and run its constructor.
 **/
int __rtld_lib_open(rtld_lib_t* ctx);


/**
 * Resolve the given symbol name to an address.
 **/
void* __rtld_lib_sym2addr(rtld_lib_t* ctx, const char* name);


/**
 * Find the symbol name closest to the given address.
 **/
const char* __rtld_lib_addr2sym(rtld_lib_t* ctx, void* addr);


/**
 * Close the lib and run its destructor.
 **/
int __rtld_lib_close(rtld_lib_t* ctx);


/**
 * Free up all memory associated with the lib.
 **/
void __rtld_lib_destroy(rtld_lib_t* ctx);


/**
 * Initialize the lib loader.
 **/
int __rtld_init(void);


/**
 * Find the path to a file with the given name.
 *
 * The search order is as follows:
 *   1 - absolute path
 *   2 - current work dir
 *   3 - /system/priv/lib/
 *   4 - /system/common/lib/
 *   5 - /system_ex/priv_ex/lib/
 *   6 - /system_ex/common_ex/lib/
 *   7 - paths in the env var LD_LIBRARY_PATH
 *   8 - /user/homebrew/lib/
 **/
int __rtld_find_file(const char *name, char* path);


/**
 * Finalize the lib loader.
 **/
int __rtld_fini(void);
