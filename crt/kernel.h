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

unsigned long kernel_get_ucred_authid(int pid);
int           kernel_set_ucred_authid(int pid, unsigned long authid);

unsigned long kernel_get_ucred_attrs(int pid);
int           kernel_set_ucred_attrs(int pid, unsigned long attrs);

int kernel_get_ucred_caps(int pid, unsigned char caps[16]);
int kernel_set_ucred_caps(int pid, const unsigned char caps[16]);

unsigned long kernel_get_root_vnode(void);
unsigned long kernel_get_proc_rootdir(int pid);
int           kernel_set_proc_rootdir(int pid, unsigned long vnode);

unsigned long kernel_dynlib_entry_addr(int pid, unsigned int handle);
int kernel_dynlib_handle(int pid, const char* basename, unsigned int *handle);
