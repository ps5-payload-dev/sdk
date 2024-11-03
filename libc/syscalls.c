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

#include "../include/ps5/payload.h"


static __attribute__ ((used)) long ptr_syscall = 0;

static payload_args_t* payload_args = 0;


asm(".intel_syntax noprefix\n"
    ".global syscall\n"
    ".type syscall @function\n"
    "syscall:\n"
    "  mov rax, rdi\n"
    "  mov rdi, rsi\n"
    "  mov rsi, rdx\n"
    "  mov rdx, rcx\n"
    "  mov r10, r8\n"
    "  mov r8,  r9\n"
    "  mov r9,  qword ptr [rsp + 8]\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global fork\n"
    ".type fork @function\n"
    "fork:\n"
    "  mov rax, 2\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global wait4\n"
    ".type wait4 @function\n"
    "wait4:\n"
    "  mov rax, 7\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global link\n"
    ".type link @function\n"
    "link:\n"
    "  mov rax, 9\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global fchdir\n"
    ".type fchdir @function\n"
    "fchdir:\n"
    "  mov rax, 13\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global mknod\n"
    ".type mknod @function\n"
    "mknod:\n"
    "  mov rax, 14\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global chown\n"
    ".type chown @function\n"
    "chown:\n"
    "  mov rax, 16\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global break\n"
    ".type break @function\n"
    "break:\n"
    "  mov rax, 17\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global mount\n"
    ".type mount @function\n"
    "mount:\n"
    "  mov rax, 21\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global unmount\n"
    ".type unmount @function\n"
    "unmount:\n"
    "  mov rax, 22\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global ptrace\n"
    ".type ptrace @function\n"
    "ptrace:\n"
    "  mov rax, 26\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global dup\n"
    ".type dup @function\n"
    "dup:\n"
    "  mov rax, 41\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global ktrace\n"
    ".type ktrace @function\n"
    "ktrace:\n"
    "  mov rax, 45\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global setlogin\n"
    ".type setlogin @function\n"
    "setlogin:\n"
    "  mov rax, 50\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global acct\n"
    ".type acct @function\n"
    "acct:\n"
    "  mov rax, 51\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global reboot\n"
    ".type reboot @function\n"
    "reboot:\n"
    "  mov rax, 55\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global revoke\n"
    ".type revoke @function\n"
    "revoke:\n"
    "  mov rax, 56\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global symlink\n"
    ".type symlink @function\n"
    "symlink:\n"
    "  mov rax, 57\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global readlink\n"
    ".type readlink @function\n"
    "readlink:\n"
    "  mov rax, 58\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global umask\n"
    ".type umask @function\n"
    "umask:\n"
    "  mov rax, 60\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global chroot\n"
    ".type chroot @function\n"
    "chroot:\n"
    "  mov rax, 61\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global vfork\n"
    ".type vfork @function\n"
    "vfork:\n"
    "  mov rax, 66\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global sbrk\n"
    ".type sbrk @function\n"
    "sbrk:\n"
    "  mov rax, 69\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global sstk\n"
    ".type sstk @function\n"
    "sstk:\n"
    "  mov rax, 70\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global vadvise\n"
    ".type vadvise @function\n"
    "vadvise:\n"
    "  mov rax, 72\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global getpgrp\n"
    ".type getpgrp @function\n"
    "getpgrp:\n"
    "  mov rax, 81\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global setpgid\n"
    ".type setpgid @function\n"
    "setpgid:\n"
    "  mov rax, 82\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global swapon\n"
    ".type swapon @function\n"
    "swapon:\n"
    "  mov rax, 85\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global fchown\n"
    ".type fchown @function\n"
    "fchown:\n"
    "  mov rax, 123\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global mkfifo\n"
    ".type mkfifo @function\n"
    "mkfifo:\n"
    "  mov rax, 132\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global adjtime\n"
    ".type adjtime @function\n"
    "adjtime:\n"
    "  mov rax, 140\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global setsid\n"
    ".type setsid @function\n"
    "setsid:\n"
    "  mov rax, 147\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global quotactl\n"
    ".type quotactl @function\n"
    "quotactl:\n"
    "  mov rax, 148\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global nlm_syscall\n"
    ".type nlm_syscall @function\n"
    "nlm_syscall:\n"
    "  mov rax, 154\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global nfssvc\n"
    ".type nfssvc @function\n"
    "nfssvc:\n"
    "  mov rax, 155\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global lgetfh\n"
    ".type lgetfh @function\n"
    "lgetfh:\n"
    "  mov rax, 160\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global getfh\n"
    ".type getfh @function\n"
    "getfh:\n"
    "  mov rax, 161\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global rtprio\n"
    ".type rtprio @function\n"
    "rtprio:\n"
    "  mov rax, 166\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global semsys\n"
    ".type semsys @function\n"
    "semsys:\n"
    "  mov rax, 169\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global msgsys\n"
    ".type msgsys @function\n"
    "msgsys:\n"
    "  mov rax, 170\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global shmsys\n"
    ".type shmsys @function\n"
    "shmsys:\n"
    "  mov rax, 171\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global setfib\n"
    ".type setfib @function\n"
    "setfib:\n"
    "  mov rax, 175\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global ntp_adjtime\n"
    ".type ntp_adjtime @function\n"
    "ntp_adjtime:\n"
    "  mov rax, 176\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global setgid\n"
    ".type setgid @function\n"
    "setgid:\n"
    "  mov rax, 181\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global pathconf\n"
    ".type pathconf @function\n"
    "pathconf:\n"
    "  mov rax, 191\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global fpathconf\n"
    ".type fpathconf @function\n"
    "fpathconf:\n"
    "  mov rax, 192\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global undelete\n"
    ".type undelete @function\n"
    "undelete:\n"
    "  mov rax, 205\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global getpgid\n"
    ".type getpgid @function\n"
    "getpgid:\n"
    "  mov rax, 207\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global semget\n"
    ".type semget @function\n"
    "semget:\n"
    "  mov rax, 221\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global semop\n"
    ".type semop @function\n"
    "semop:\n"
    "  mov rax, 222\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global msgget\n"
    ".type msgget @function\n"
    "msgget:\n"
    "  mov rax, 225\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global msgsnd\n"
    ".type msgsnd @function\n"
    "msgsnd:\n"
    "  mov rax, 226\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global msgrcv\n"
    ".type msgrcv @function\n"
    "msgrcv:\n"
    "  mov rax, 227\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global shmat\n"
    ".type shmat @function\n"
    "shmat:\n"
    "  mov rax, 228\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global shmdt\n"
    ".type shmdt @function\n"
    "shmdt:\n"
    "  mov rax, 230\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global shmget\n"
    ".type shmget @function\n"
    "shmget:\n"
    "  mov rax, 231\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global ffclock_getcounter\n"
    ".type ffclock_getcounter @function\n"
    "ffclock_getcounter:\n"
    "  mov rax, 241\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global ffclock_setestimate\n"
    ".type ffclock_setestimate @function\n"
    "ffclock_setestimate:\n"
    "  mov rax, 242\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global ffclock_getestimate\n"
    ".type ffclock_getestimate @function\n"
    "ffclock_getestimate:\n"
    "  mov rax, 243\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global clock_nanosleep\n"
    ".type clock_nanosleep @function\n"
    "clock_nanosleep:\n"
    "  mov rax, 244\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global clock_getcpuclockid2\n"
    ".type clock_getcpuclockid2 @function\n"
    "clock_getcpuclockid2:\n"
    "  mov rax, 247\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global ntp_gettime\n"
    ".type ntp_gettime @function\n"
    "ntp_gettime:\n"
    "  mov rax, 248\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global minherit\n"
    ".type minherit @function\n"
    "minherit:\n"
    "  mov rax, 250\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global rfork\n"
    ".type rfork @function\n"
    "rfork:\n"
    "  mov rax, 251\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global lchown\n"
    ".type lchown @function\n"
    "lchown:\n"
    "  mov rax, 254\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global aio_read\n"
    ".type aio_read @function\n"
    "aio_read:\n"
    "  mov rax, 255\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global aio_write\n"
    ".type aio_write @function\n"
    "aio_write:\n"
    "  mov rax, 256\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global lio_listio\n"
    ".type lio_listio @function\n"
    "lio_listio:\n"
    "  mov rax, 257\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global lchmod\n"
    ".type lchmod @function\n"
    "lchmod:\n"
    "  mov rax, 274\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global lutimes\n"
    ".type lutimes @function\n"
    "lutimes:\n"
    "  mov rax, 276\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global nstat\n"
    ".type nstat @function\n"
    "nstat:\n"
    "  mov rax, 278\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global nfstat\n"
    ".type nfstat @function\n"
    "nfstat:\n"
    "  mov rax, 279\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global nlstat\n"
    ".type nlstat @function\n"
    "nlstat:\n"
    "  mov rax, 280\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global fhopen\n"
    ".type fhopen @function\n"
    "fhopen:\n"
    "  mov rax, 298\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global fhstat\n"
    ".type fhstat @function\n"
    "fhstat:\n"
    "  mov rax, 299\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global modnext\n"
    ".type modnext @function\n"
    "modnext:\n"
    "  mov rax, 300\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global modstat\n"
    ".type modstat @function\n"
    "modstat:\n"
    "  mov rax, 301\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global modfnext\n"
    ".type modfnext @function\n"
    "modfnext:\n"
    "  mov rax, 302\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global modfind\n"
    ".type modfind @function\n"
    "modfind:\n"
    "  mov rax, 303\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global kldload\n"
    ".type kldload @function\n"
    "kldload:\n"
    "  mov rax, 304\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global kldunload\n"
    ".type kldunload @function\n"
    "kldunload:\n"
    "  mov rax, 305\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global kldfind\n"
    ".type kldfind @function\n"
    "kldfind:\n"
    "  mov rax, 306\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global kldnext\n"
    ".type kldnext @function\n"
    "kldnext:\n"
    "  mov rax, 307\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global kldstat\n"
    ".type kldstat @function\n"
    "kldstat:\n"
    "  mov rax, 308\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global kldfirstmod\n"
    ".type kldfirstmod @function\n"
    "kldfirstmod:\n"
    "  mov rax, 309\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global setresuid\n"
    ".type setresuid @function\n"
    "setresuid:\n"
    "  mov rax, 311\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global setresgid\n"
    ".type setresgid @function\n"
    "setresgid:\n"
    "  mov rax, 312\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global aio_return\n"
    ".type aio_return @function\n"
    "aio_return:\n"
    "  mov rax, 314\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global aio_suspend\n"
    ".type aio_suspend @function\n"
    "aio_suspend:\n"
    "  mov rax, 315\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global aio_cancel\n"
    ".type aio_cancel @function\n"
    "aio_cancel:\n"
    "  mov rax, 316\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global aio_error\n"
    ".type aio_error @function\n"
    "aio_error:\n"
    "  mov rax, 317\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global yield\n"
    ".type yield @function\n"
    "yield:\n"
    "  mov rax, 321\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global utrace\n"
    ".type utrace @function\n"
    "utrace:\n"
    "  mov rax, 335\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global kldsym\n"
    ".type kldsym @function\n"
    "kldsym:\n"
    "  mov rax, 337\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global jail\n"
    ".type jail @function\n"
    "jail:\n"
    "  mov rax, 338\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global nnpfs_syscall\n"
    ".type nnpfs_syscall @function\n"
    "nnpfs_syscall:\n"
    "  mov rax, 339\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global __acl_get_file\n"
    ".type __acl_get_file @function\n"
    "__acl_get_file:\n"
    "  mov rax, 347\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global __acl_set_file\n"
    ".type __acl_set_file @function\n"
    "__acl_set_file:\n"
    "  mov rax, 348\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global __acl_get_fd\n"
    ".type __acl_get_fd @function\n"
    "__acl_get_fd:\n"
    "  mov rax, 349\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global __acl_set_fd\n"
    ".type __acl_set_fd @function\n"
    "__acl_set_fd:\n"
    "  mov rax, 350\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global __acl_delete_file\n"
    ".type __acl_delete_file @function\n"
    "__acl_delete_file:\n"
    "  mov rax, 351\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global __acl_delete_fd\n"
    ".type __acl_delete_fd @function\n"
    "__acl_delete_fd:\n"
    "  mov rax, 352\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global __acl_aclcheck_file\n"
    ".type __acl_aclcheck_file @function\n"
    "__acl_aclcheck_file:\n"
    "  mov rax, 353\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global __acl_aclcheck_fd\n"
    ".type __acl_aclcheck_fd @function\n"
    "__acl_aclcheck_fd:\n"
    "  mov rax, 354\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global extattrctl\n"
    ".type extattrctl @function\n"
    "extattrctl:\n"
    "  mov rax, 355\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global extattr_set_file\n"
    ".type extattr_set_file @function\n"
    "extattr_set_file:\n"
    "  mov rax, 356\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global extattr_get_file\n"
    ".type extattr_get_file @function\n"
    "extattr_get_file:\n"
    "  mov rax, 357\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global extattr_delete_file\n"
    ".type extattr_delete_file @function\n"
    "extattr_delete_file:\n"
    "  mov rax, 358\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global aio_waitcomplete\n"
    ".type aio_waitcomplete @function\n"
    "aio_waitcomplete:\n"
    "  mov rax, 359\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global getresuid\n"
    ".type getresuid @function\n"
    "getresuid:\n"
    "  mov rax, 360\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global getresgid\n"
    ".type getresgid @function\n"
    "getresgid:\n"
    "  mov rax, 361\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global extattr_set_fd\n"
    ".type extattr_set_fd @function\n"
    "extattr_set_fd:\n"
    "  mov rax, 371\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global extattr_get_fd\n"
    ".type extattr_get_fd @function\n"
    "extattr_get_fd:\n"
    "  mov rax, 372\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global extattr_delete_fd\n"
    ".type extattr_delete_fd @function\n"
    "extattr_delete_fd:\n"
    "  mov rax, 373\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global __setugid\n"
    ".type __setugid @function\n"
    "__setugid:\n"
    "  mov rax, 374\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global eaccess\n"
    ".type eaccess @function\n"
    "eaccess:\n"
    "  mov rax, 376\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global afs3_syscall\n"
    ".type afs3_syscall @function\n"
    "afs3_syscall:\n"
    "  mov rax, 377\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global nmount\n"
    ".type nmount @function\n"
    "nmount:\n"
    "  mov rax, 378\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global __mac_get_proc\n"
    ".type __mac_get_proc @function\n"
    "__mac_get_proc:\n"
    "  mov rax, 384\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global __mac_set_proc\n"
    ".type __mac_set_proc @function\n"
    "__mac_set_proc:\n"
    "  mov rax, 385\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global __mac_get_fd\n"
    ".type __mac_get_fd @function\n"
    "__mac_get_fd:\n"
    "  mov rax, 386\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global __mac_get_file\n"
    ".type __mac_get_file @function\n"
    "__mac_get_file:\n"
    "  mov rax, 387\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global __mac_set_fd\n"
    ".type __mac_set_fd @function\n"
    "__mac_set_fd:\n"
    "  mov rax, 388\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global __mac_set_file\n"
    ".type __mac_set_file @function\n"
    "__mac_set_file:\n"
    "  mov rax, 389\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global kenv\n"
    ".type kenv @function\n"
    "kenv:\n"
    "  mov rax, 390\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global lchflags\n"
    ".type lchflags @function\n"
    "lchflags:\n"
    "  mov rax, 391\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global mac_syscall\n"
    ".type mac_syscall @function\n"
    "mac_syscall:\n"
    "  mov rax, 394\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global getfsstat\n"
    ".type getfsstat @function\n"
    "getfsstat:\n"
    "  mov rax, 395\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global statfs\n"
    ".type statfs @function\n"
    "statfs:\n"
    "  mov rax, 396\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global fstatfs\n"
    ".type fstatfs @function\n"
    "fstatfs:\n"
    "  mov rax, 397\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global fhstatfs\n"
    ".type fhstatfs @function\n"
    "fhstatfs:\n"
    "  mov rax, 398\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global __mac_get_pid\n"
    ".type __mac_get_pid @function\n"
    "__mac_get_pid:\n"
    "  mov rax, 409\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global __mac_get_link\n"
    ".type __mac_get_link @function\n"
    "__mac_get_link:\n"
    "  mov rax, 410\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global __mac_set_link\n"
    ".type __mac_set_link @function\n"
    "__mac_set_link:\n"
    "  mov rax, 411\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global extattr_set_link\n"
    ".type extattr_set_link @function\n"
    "extattr_set_link:\n"
    "  mov rax, 412\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global extattr_get_link\n"
    ".type extattr_get_link @function\n"
    "extattr_get_link:\n"
    "  mov rax, 413\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global extattr_delete_link\n"
    ".type extattr_delete_link @function\n"
    "extattr_delete_link:\n"
    "  mov rax, 414\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global __mac_execve\n"
    ".type __mac_execve @function\n"
    "__mac_execve:\n"
    "  mov rax, 415\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global swapoff\n"
    ".type swapoff @function\n"
    "swapoff:\n"
    "  mov rax, 424\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global __acl_get_link\n"
    ".type __acl_get_link @function\n"
    "__acl_get_link:\n"
    "  mov rax, 425\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global __acl_set_link\n"
    ".type __acl_set_link @function\n"
    "__acl_set_link:\n"
    "  mov rax, 426\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global __acl_delete_link\n"
    ".type __acl_delete_link @function\n"
    "__acl_delete_link:\n"
    "  mov rax, 427\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global __acl_aclcheck_link\n"
    ".type __acl_aclcheck_link @function\n"
    "__acl_aclcheck_link:\n"
    "  mov rax, 428\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global thr_create\n"
    ".type thr_create @function\n"
    "thr_create:\n"
    "  mov rax, 430\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global thr_exit\n"
    ".type thr_exit @function\n"
    "thr_exit:\n"
    "  mov rax, 431\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global thr_self\n"
    ".type thr_self @function\n"
    "thr_self:\n"
    "  mov rax, 432\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global thr_kill\n"
    ".type thr_kill @function\n"
    "thr_kill:\n"
    "  mov rax, 433\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global jail_attach\n"
    ".type jail_attach @function\n"
    "jail_attach:\n"
    "  mov rax, 436\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global extattr_list_fd\n"
    ".type extattr_list_fd @function\n"
    "extattr_list_fd:\n"
    "  mov rax, 437\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global extattr_list_file\n"
    ".type extattr_list_file @function\n"
    "extattr_list_file:\n"
    "  mov rax, 438\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global extattr_list_link\n"
    ".type extattr_list_link @function\n"
    "extattr_list_link:\n"
    "  mov rax, 439\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global thr_suspend\n"
    ".type thr_suspend @function\n"
    "thr_suspend:\n"
    "  mov rax, 442\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global thr_wake\n"
    ".type thr_wake @function\n"
    "thr_wake:\n"
    "  mov rax, 443\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global kldunloadf\n"
    ".type kldunloadf @function\n"
    "kldunloadf:\n"
    "  mov rax, 444\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global audit\n"
    ".type audit @function\n"
    "audit:\n"
    "  mov rax, 445\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global auditon\n"
    ".type auditon @function\n"
    "auditon:\n"
    "  mov rax, 446\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global getauid\n"
    ".type getauid @function\n"
    "getauid:\n"
    "  mov rax, 447\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global setauid\n"
    ".type setauid @function\n"
    "setauid:\n"
    "  mov rax, 448\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global getaudit\n"
    ".type getaudit @function\n"
    "getaudit:\n"
    "  mov rax, 449\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global setaudit\n"
    ".type setaudit @function\n"
    "setaudit:\n"
    "  mov rax, 450\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global getaudit_addr\n"
    ".type getaudit_addr @function\n"
    "getaudit_addr:\n"
    "  mov rax, 451\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global setaudit_addr\n"
    ".type setaudit_addr @function\n"
    "setaudit_addr:\n"
    "  mov rax, 452\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global auditctl\n"
    ".type auditctl @function\n"
    "auditctl:\n"
    "  mov rax, 453\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global thr_new\n"
    ".type thr_new @function\n"
    "thr_new:\n"
    "  mov rax, 455\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global kmq_open\n"
    ".type kmq_open @function\n"
    "kmq_open:\n"
    "  mov rax, 457\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global kmq_setattr\n"
    ".type kmq_setattr @function\n"
    "kmq_setattr:\n"
    "  mov rax, 458\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global kmq_timedreceive\n"
    ".type kmq_timedreceive @function\n"
    "kmq_timedreceive:\n"
    "  mov rax, 459\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global kmq_timedsend\n"
    ".type kmq_timedsend @function\n"
    "kmq_timedsend:\n"
    "  mov rax, 460\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global kmq_notify\n"
    ".type kmq_notify @function\n"
    "kmq_notify:\n"
    "  mov rax, 461\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global kmq_unlink\n"
    ".type kmq_unlink @function\n"
    "kmq_unlink:\n"
    "  mov rax, 462\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global abort2\n"
    ".type abort2 @function\n"
    "abort2:\n"
    "  mov rax, 463\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global thr_set_name\n"
    ".type thr_set_name @function\n"
    "thr_set_name:\n"
    "  mov rax, 464\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global aio_fsync\n"
    ".type aio_fsync @function\n"
    "aio_fsync:\n"
    "  mov rax, 465\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global sctp_peeloff\n"
    ".type sctp_peeloff @function\n"
    "sctp_peeloff:\n"
    "  mov rax, 471\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global sctp_generic_sendmsg\n"
    ".type sctp_generic_sendmsg @function\n"
    "sctp_generic_sendmsg:\n"
    "  mov rax, 472\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global sctp_generic_sendmsg_iov\n"
    ".type sctp_generic_sendmsg_iov @function\n"
    "sctp_generic_sendmsg_iov:\n"
    "  mov rax, 473\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global sctp_generic_recvmsg\n"
    ".type sctp_generic_recvmsg @function\n"
    "sctp_generic_recvmsg:\n"
    "  mov rax, 474\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global thr_kill2\n"
    ".type thr_kill2 @function\n"
    "thr_kill2:\n"
    "  mov rax, 481\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global cpuset\n"
    ".type cpuset @function\n"
    "cpuset:\n"
    "  mov rax, 484\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global cpuset_setid\n"
    ".type cpuset_setid @function\n"
    "cpuset_setid:\n"
    "  mov rax, 485\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global faccessat\n"
    ".type faccessat @function\n"
    "faccessat:\n"
    "  mov rax, 489\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global fchmodat\n"
    ".type fchmodat @function\n"
    "fchmodat:\n"
    "  mov rax, 490\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global fchownat\n"
    ".type fchownat @function\n"
    "fchownat:\n"
    "  mov rax, 491\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global fexecve\n"
    ".type fexecve @function\n"
    "fexecve:\n"
    "  mov rax, 492\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global fstatat\n"
    ".type fstatat @function\n"
    "fstatat:\n"
    "  mov rax, 493\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global futimesat\n"
    ".type futimesat @function\n"
    "futimesat:\n"
    "  mov rax, 494\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global linkat\n"
    ".type linkat @function\n"
    "linkat:\n"
    "  mov rax, 495\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global mkdirat\n"
    ".type mkdirat @function\n"
    "mkdirat:\n"
    "  mov rax, 496\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global mkfifoat\n"
    ".type mkfifoat @function\n"
    "mkfifoat:\n"
    "  mov rax, 497\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global mknodat\n"
    ".type mknodat @function\n"
    "mknodat:\n"
    "  mov rax, 498\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global openat\n"
    ".type openat @function\n"
    "openat:\n"
    "  mov rax, 499\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global readlinkat\n"
    ".type readlinkat @function\n"
    "readlinkat:\n"
    "  mov rax, 500\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global renameat\n"
    ".type renameat @function\n"
    "renameat:\n"
    "  mov rax, 501\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global symlinkat\n"
    ".type symlinkat @function\n"
    "symlinkat:\n"
    "  mov rax, 502\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global unlinkat\n"
    ".type unlinkat @function\n"
    "unlinkat:\n"
    "  mov rax, 503\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global posix_openpt\n"
    ".type posix_openpt @function\n"
    "posix_openpt:\n"
    "  mov rax, 504\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global gssd_syscall\n"
    ".type gssd_syscall @function\n"
    "gssd_syscall:\n"
    "  mov rax, 505\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global jail_get\n"
    ".type jail_get @function\n"
    "jail_get:\n"
    "  mov rax, 506\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global jail_set\n"
    ".type jail_set @function\n"
    "jail_set:\n"
    "  mov rax, 507\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global jail_remove\n"
    ".type jail_remove @function\n"
    "jail_remove:\n"
    "  mov rax, 508\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global closefrom\n"
    ".type closefrom @function\n"
    "closefrom:\n"
    "  mov rax, 509\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global semctl\n"
    ".type semctl @function\n"
    "semctl:\n"
    "  mov rax, 510\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global msgctl\n"
    ".type msgctl @function\n"
    "msgctl:\n"
    "  mov rax, 511\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global shmctl\n"
    ".type shmctl @function\n"
    "shmctl:\n"
    "  mov rax, 512\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global lpathconf\n"
    ".type lpathconf @function\n"
    "lpathconf:\n"
    "  mov rax, 513\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global __cap_rights_get\n"
    ".type __cap_rights_get @function\n"
    "__cap_rights_get:\n"
    "  mov rax, 515\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global cap_enter\n"
    ".type cap_enter @function\n"
    "cap_enter:\n"
    "  mov rax, 516\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global cap_getmode\n"
    ".type cap_getmode @function\n"
    "cap_getmode:\n"
    "  mov rax, 517\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global pdfork\n"
    ".type pdfork @function\n"
    "pdfork:\n"
    "  mov rax, 518\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global pdkill\n"
    ".type pdkill @function\n"
    "pdkill:\n"
    "  mov rax, 519\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global pdgetpid\n"
    ".type pdgetpid @function\n"
    "pdgetpid:\n"
    "  mov rax, 520\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global getloginclass\n"
    ".type getloginclass @function\n"
    "getloginclass:\n"
    "  mov rax, 523\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global setloginclass\n"
    ".type setloginclass @function\n"
    "setloginclass:\n"
    "  mov rax, 524\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global rctl_get_racct\n"
    ".type rctl_get_racct @function\n"
    "rctl_get_racct:\n"
    "  mov rax, 525\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global rctl_get_rules\n"
    ".type rctl_get_rules @function\n"
    "rctl_get_rules:\n"
    "  mov rax, 526\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global rctl_get_limits\n"
    ".type rctl_get_limits @function\n"
    "rctl_get_limits:\n"
    "  mov rax, 527\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global rctl_add_rule\n"
    ".type rctl_add_rule @function\n"
    "rctl_add_rule:\n"
    "  mov rax, 528\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global rctl_remove_rule\n"
    ".type rctl_remove_rule @function\n"
    "rctl_remove_rule:\n"
    "  mov rax, 529\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global posix_fallocate\n"
    ".type posix_fallocate @function\n"
    "posix_fallocate:\n"
    "  mov rax, 530\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global posix_fadvise\n"
    ".type posix_fadvise @function\n"
    "posix_fadvise:\n"
    "  mov rax, 531\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global wait6\n"
    ".type wait6 @function\n"
    "wait6:\n"
    "  mov rax, 532\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global cap_rights_limit\n"
    ".type cap_rights_limit @function\n"
    "cap_rights_limit:\n"
    "  mov rax, 533\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global cap_ioctls_limit\n"
    ".type cap_ioctls_limit @function\n"
    "cap_ioctls_limit:\n"
    "  mov rax, 534\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global cap_ioctls_get\n"
    ".type cap_ioctls_get @function\n"
    "cap_ioctls_get:\n"
    "  mov rax, 535\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global cap_fcntls_limit\n"
    ".type cap_fcntls_limit @function\n"
    "cap_fcntls_limit:\n"
    "  mov rax, 536\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global cap_fcntls_get\n"
    ".type cap_fcntls_get @function\n"
    "cap_fcntls_get:\n"
    "  mov rax, 537\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global bindat\n"
    ".type bindat @function\n"
    "bindat:\n"
    "  mov rax, 538\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global connectat\n"
    ".type connectat @function\n"
    "connectat:\n"
    "  mov rax, 539\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global chflagsat\n"
    ".type chflagsat @function\n"
    "chflagsat:\n"
    "  mov rax, 540\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


/*
  TODO: not currently supported
asm(".intel_syntax noprefix\n"
    ".global accept4\n"
    ".type accept4 @function\n"
    "accept4:\n"
    "  mov rax, 541\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );
*/

asm(".intel_syntax noprefix\n"
    ".global aio_mlock\n"
    ".type aio_mlock @function\n"
    "aio_mlock:\n"
    "  mov rax, 543\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global procctl\n"
    ".type procctl @function\n"
    "procctl:\n"
    "  mov rax, 544\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global ppoll\n"
    ".type ppoll @function\n"
    "ppoll:\n"
    "  mov rax, 545\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global futimens\n"
    ".type futimens @function\n"
    "futimens:\n"
    "  mov rax, 546\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global utimensat\n"
    ".type utimensat @function\n"
    "utimensat:\n"
    "  mov rax, 547\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global numa_getaffinity\n"
    ".type numa_getaffinity @function\n"
    "numa_getaffinity:\n"
    "  mov rax, 548\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


asm(".intel_syntax noprefix\n"
    ".global numa_setaffinity\n"
    ".type numa_setaffinity @function\n"
    "numa_setaffinity:\n"
    "  mov rax, 549\n"
    "  mov r10, rcx\n"
    "  jmp qword ptr [rip + ptr_syscall]\n"
    "  ret\n"
    );


payload_args_t*
payload_get_args(void) {
  return payload_args;
}


__attribute__((constructor(105))) static void
syscall_constructor(int argc, char** argv, char** envp, payload_args_t *args) {
  int (*sceKernelDlsym)(int, const char*, void*) = 0;

  if(args->sys_dynlib_dlsym(0x1, "sceKernelDlsym", &sceKernelDlsym)) {
    args->sys_dynlib_dlsym(0x2001, "sceKernelDlsym", &sceKernelDlsym);
  }
  if(sceKernelDlsym == args->sys_dynlib_dlsym) {
    if(args->sys_dynlib_dlsym(0x1, "getpid", &ptr_syscall)) {
      args->sys_dynlib_dlsym(0x2001, "getpid", &ptr_syscall);
    }
  } else {
    ptr_syscall = (long)args->sys_dynlib_dlsym;
  }

  ptr_syscall += 0xa; // jump directly to the syscall instruction
}
