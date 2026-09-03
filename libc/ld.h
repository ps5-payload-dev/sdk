/* Copyright (C) 2026 John Törnblom

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

#include <sys/types.h>
#include <termios.h>

#include "upty.h"

#define LD_CANON_MAX 1024


typedef struct ld_ops {
  void (*to_slave)(void *ctx, const void *buf, size_t len);
  void (*to_remote)(void *ctx, const void *buf, size_t len);
  void (*signal)(void *ctx, int sig);
  void (*eof)(void *ctx);
} ld_ops_t;


typedef struct ld {
  const ld_ops_t *ops;
  upty_t *pty;
  void *ctx;

  unsigned char canon[LD_CANON_MAX];
  unsigned char width[LD_CANON_MAX];
  size_t canon_len;
  int stopped;
  int lnext;
} ld_t;


void ld_init(ld_t *ld, upty_t *pty, const ld_ops_t *ops, void *ctx);
void ld_input(ld_t *ld, const void *buf, size_t len);
void ld_output(ld_t *ld, const void *buf, size_t len);
void ld_termios_changed(ld_t *ld);
