#!/usr/bin/env python3
# encoding: utf-8
# Copyright (C) 2024 John Törnblom
#
# This program is free software; you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; see the file COPYING. If not see
# <http://www.gnu.org/licenses/>.

import os
import string


print('''
static __attribute__ ((used)) long ptr_syscall = 0;
asm(".intel_syntax noprefix\\n"
    ".global syscall\\n"
    ".type syscall @function\\n"
    "syscall:\\n"
    "  mov rax, rdi\\n"
    "  mov rdi, rsi\\n"
    "  mov rsi, rdx\\n"
    "  mov rdx, rcx\\n"
    "  mov r10, r8\\n"
    "  mov r8,  r9\\n"
    "  mov r9,  qword ptr [rsp + 8]\\n"
    "  jmp qword ptr [rip + ptr_syscall]\\n"
    "  ret\\n"
    );
''')


syscall_tmpl = string.Template('''
asm(".intel_syntax noprefix\\n"
    ".global $sysname\\n"
    ".type $sysname @function\\n"
    "$sysname:\\n"
    "  mov rax, $sysno\\n"
    "  mov r10, rcx\\n"
    "  jmp qword ptr [rip + ptr_syscall]\\n"
    "  ret\\n"
    );
''')

header = os.path.dirname(__file__)
with open(f'{header}/../include/freebsd/sys/syscall.h') as f:
    s = f.read()
    for line in s.splitlines():
        if not line.startswith('#define\tSYS'):
            continue

        line = line[12:].strip()
        name, no = line.split()
        name = name.strip()
        no = int(no.strip())

        if name in ['syscall', 'pipe', 'MAXSYSCALL']:
            continue

        if name.startswith('freebsd'):
            continue

        print(syscall_tmpl.substitute(sysname=name, sysno=no))


print('''
#include "payload.h"

int __syscall_init(payload_args_t* args) {
  int error;
  if(args->sceKernelDlsym(0x1, "getpid", &ptr_syscall)) {
    if((error=args->sceKernelDlsym(0x2001, "getpid", &ptr_syscall))) {
      return error;
    }
  }

  // jump directly to the syscall instruction
  // in getpid (provided by libkernel)
  ptr_syscall += 0xa;
  return 0;
}
''')
