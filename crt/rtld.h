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
  void* (*sym)(struct rtld_lib* ctx, const char* name);
  int (*close)(struct rtld_lib* ctx);
  void (*destroy)(struct rtld_lib* ctx);

  char *soname;

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
 * Resolve a symbol in the lib.
 **/
void* __rtld_lib_sym(rtld_lib_t* ctx, const char* name);


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
 * Finalize the lib loader.
 **/
int __rtld_fini(void);
