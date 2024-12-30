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

#include <stdint.h>


/**
 * Data structure that capture the args passed to _start().
 **/
typedef struct payload_args {
  int (*sys_dynlib_dlsym)(int, const char*, void*);
  int* rwpipe;
  int* rwpair;

  intptr_t kpipe_addr;
  intptr_t kdata_base_addr;

  int* payloadout;
} payload_args_t;


/**
 * Get the arguments that was passed to _start().
 **/
payload_args_t* payload_get_args(void);


/**
 * Exit the payload.
 *
 * If the payload is running inside a hijacked process,
 * the process will continue to run from where it left off.
 **/
void payload_exit(int exit_code);
