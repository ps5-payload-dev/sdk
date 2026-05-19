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


typedef struct payload_args0 {
  int (*sys_dynlib_dlsym)(int, const char*, void*);
  int  *rwpipe;
  int  *rwpair;
  long  kpipe_addr;
  long  kdata_base_addr;
  int  *payloadout;
} payload_args0_t;


typedef struct payload_args1 {
  unsigned long pa_structsize;
  int           pa_master_pipe[2];
  int           pa_victim_pipe[2];
  unsigned long pa_getpid;
  unsigned long pa_allproc;
} payload_args1_t;


/**
 * Implemented in crt.c
 **/
payload_args0_t* payload_get_args(void);
void payload_exit(int exit_code);
