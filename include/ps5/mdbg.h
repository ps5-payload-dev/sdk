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
#include <unistd.h>


/**
 * Copy data out from a process with the given pid at the given address.
 **/
int mdbg_copyout(pid_t pid, intptr_t addr, void *buf, size_t len);


/**
 * Copy data into a process with the given pid at the given address.
 **/
int mdbg_copyin(pid_t pid, const void *buf, intptr_t addr, size_t len);


int mdbg_setchar(pid_t pid, intptr_t addr, char val);
int mdbg_setint(pid_t pid, intptr_t addr, int val);
int mdbg_setlong(pid_t pid, intptr_t addr, long val);

