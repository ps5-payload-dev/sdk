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

#define SYS_read        3
#define SYS_write       4
#define SYS_getpid      20
#define SYS_access      33
#define SYS_setsockopt  105
#define SYS_sysctl      202
#define SYS_mdbg_call   573
#define SYS_sprx_dlsym  591
#define SYS_sprx_load   594
#define SYS_sprx_unload 595


long syscall(long sysno, ...);
