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
#include "klog.h"
#include "mdbg.h"
#include "payload.h"
#include "syscall.h"


/**
 * Patch retail distributions of sceKernelSpawn() that ignore the dbg parameter.
 *
 * At offset 52, replace 0x00000000a845c748l with 0x90909090a8758948l, i.e.,
 *
 *            mov    QWORD PTR [rbp-0x58],0x0
 * becomes
 *            mov    QWORD PTR [rbp-0x58],rsi
 *            nop
 *            nop
 *            nop
 *            nop
 **/
static int
patch_sceKernelSpawn(void) {
  unsigned long loc;
  unsigned long val;

  if(!(loc=kernel_dynlib_dlsym(-1, 0x1, "sceKernelSpawn"))) {
    if(!(loc=kernel_dynlib_dlsym(-1, 0x2001, "sceKernelSpawn"))) {
      return -1;
    }
  }

  loc += 52;
  if(mdbg_copyout(-1, loc, &val, sizeof(val))) {
    klog_perror("mdbg_copyout");
    return -1;
  }

  // sanity checks
  if(val == 0x90909090a8758948l) {
    return 0;

  } else if(val != 0x00000000a845c748l) {
    klog_puts("patch_sceKernelSpawn: wrong offset");
    return -1;
  }

  val = 0x90909090a8758948l;
  if(mdbg_copyin(-1, &val, loc, sizeof(val))) {
    klog_perror("mdbg_copyin");
    return -1;
  }

  return 0;
}


static int
patch_kernel_ucred(void) {
  int pid = __syscall(SYS_getpid);
  unsigned char caps[16];
  unsigned long attrs;

  if(kernel_get_ucred_caps(pid, caps)) {
    klog_puts("kernel_get_ucred_caps failed");
    return -1;
  }
  if(!(attrs=kernel_get_ucred_attrs(pid))) {
    klog_puts("kernel_get_ucred_attrs failed");
    return -1;
  }

  caps[5]  = 0x1c; // ??
  caps[7]  = 0x40; // jail related?
  caps[15] |= 0x40; // jitshm
  attrs    |= 0x80; // ptrace

  if(kernel_set_ucred_caps(pid, caps)) {
    klog_puts("kernel_set_ucred_caps failed");
    return -1;
  }
  if(kernel_set_ucred_attrs(pid, attrs)) {
    klog_puts("kernel_set_ucred_attrs failed");
    return -1;
  }

  return 0;
}


int
__patch_init(void) {
  int error;

  if((error=patch_sceKernelSpawn())) {
    return error;
  }
  if((error=patch_kernel_ucred())) {
    return error;
  }

  return 0;
}
