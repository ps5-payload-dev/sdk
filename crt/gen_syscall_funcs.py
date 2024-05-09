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

missing_funcs = [(2, 'fork'),
                 (7, 'wait4'),
                 (9, 'link'),
                 (13, 'fchdir'),
                 (14, 'mknod'),
                 (16, 'chown'),
                 (17, 'break'),
                 (21, 'mount'),
                 (22, 'unmount'),
                 (26, 'ptrace'),
                 (41, 'dup'),
                 (45, 'ktrace'),
                 (50, 'setlogin'),
                 (51, 'acct'),
                 (55, 'reboot'),
                 (56, 'revoke'),
                 (57, 'symlink'),
                 (58, 'readlink'),
                 (60, 'umask'),
                 (61, 'chroot'),
                 (66, 'vfork'),
                 (69, 'sbrk'),
                 (70, 'sstk'),
                 (72, 'vadvise'),
                 (81, 'getpgrp'),
                 (82, 'setpgid'),
                 (85, 'swapon'),
                 (123, 'fchown'),
                 (132, 'mkfifo'),
                 (140, 'adjtime'),
                 (147, 'setsid'),
                 (148, 'quotactl'),
                 (154, 'nlm_syscall'),
                 (155, 'nfssvc'),
                 (160, 'lgetfh'),
                 (161, 'getfh'),
                 (166, 'rtprio'),
                 (169, 'semsys'),
                 (170, 'msgsys'),
                 (171, 'shmsys'),
                 (175, 'setfib'),
                 (176, 'ntp_adjtime'),
                 (181, 'setgid'),
                 (191, 'pathconf'),
                 (192, 'fpathconf'),
                 (198, '__syscall'),
                 (205, 'undelete'),
                 (207, 'getpgid'),
                 (221, 'semget'),
                 (222, 'semop'),
                 (225, 'msgget'),
                 (226, 'msgsnd'),
                 (227, 'msgrcv'),
                 (228, 'shmat'),
                 (230, 'shmdt'),
                 (231, 'shmget'),
                 (241, 'ffclock_getcounter'),
                 (242, 'ffclock_setestimate'),
                 (243, 'ffclock_getestimate'),
                 (244, 'clock_nanosleep'),
                 (247, 'clock_getcpuclockid2'),
                 (248, 'ntp_gettime'),
                 (250, 'minherit'),
                 (251, 'rfork'),
                 (254, 'lchown'),
                 (255, 'aio_read'),
                 (256, 'aio_write'),
                 (257, 'lio_listio'),
                 (274, 'lchmod'),
                 (276, 'lutimes'),
                 (278, 'nstat'),
                 (279, 'nfstat'),
                 (280, 'nlstat'),
                 (298, 'fhopen'),
                 (299, 'fhstat'),
                 (300, 'modnext'),
                 (301, 'modstat'),
                 (302, 'modfnext'),
                 (303, 'modfind'),
                 (304, 'kldload'),
                 (305, 'kldunload'),
                 (306, 'kldfind'),
                 (307, 'kldnext'),
                 (308, 'kldstat'),
                 (309, 'kldfirstmod'),
                 (311, 'setresuid'),
                 (312, 'setresgid'),
                 (314, 'aio_return'),
                 (315, 'aio_suspend'),
                 (316, 'aio_cancel'),
                 (317, 'aio_error'),
                 (321, 'yield'),
                 (335, 'utrace'),
                 (337, 'kldsym'),
                 (338, 'jail'),
                 (339, 'nnpfs_syscall'),
                 (347, '__acl_get_file'),
                 (348, '__acl_set_file'),
                 (349, '__acl_get_fd'),
                 (350, '__acl_set_fd'),
                 (351, '__acl_delete_file'),
                 (352, '__acl_delete_fd'),
                 (353, '__acl_aclcheck_file'),
                 (354, '__acl_aclcheck_fd'),
                 (355, 'extattrctl'),
                 (356, 'extattr_set_file'),
                 (357, 'extattr_get_file'),
                 (358, 'extattr_delete_file'),
                 (359, 'aio_waitcomplete'),
                 (360, 'getresuid'),
                 (361, 'getresgid'),
                 (371, 'extattr_set_fd'),
                 (372, 'extattr_get_fd'),
                 (373, 'extattr_delete_fd'),
                 (374, '__setugid'),
                 (376, 'eaccess'),
                 (377, 'afs3_syscall'),
                 (378, 'nmount'),
                 (384, '__mac_get_proc'),
                 (385, '__mac_set_proc'),
                 (386, '__mac_get_fd'),
                 (387, '__mac_get_file'),
                 (388, '__mac_set_fd'),
                 (389, '__mac_set_file'),
                 (390, 'kenv'),
                 (391, 'lchflags'),
                 (394, 'mac_syscall'),
                 (395, 'getfsstat'),
                 (396, 'statfs'),
                 (397, 'fstatfs'),
                 (398, 'fhstatfs'),
                 (409, '__mac_get_pid'),
                 (410, '__mac_get_link'),
                 (411, '__mac_set_link'),
                 (412, 'extattr_set_link'),
                 (413, 'extattr_get_link'),
                 (414, 'extattr_delete_link'),
                 (415, '__mac_execve'),
                 (424, 'swapoff'),
                 (425, '__acl_get_link'),
                 (426, '__acl_set_link'),
                 (427, '__acl_delete_link'),
                 (428, '__acl_aclcheck_link'),
                 (430, 'thr_create'),
                 (431, 'thr_exit'),
                 (432, 'thr_self'),
                 (433, 'thr_kill'),
                 (436, 'jail_attach'),
                 (437, 'extattr_list_fd'),
                 (438, 'extattr_list_file'),
                 (439, 'extattr_list_link'),
                 (442, 'thr_suspend'),
                 (443, 'thr_wake'),
                 (444, 'kldunloadf'),
                 (445, 'audit'),
                 (446, 'auditon'),
                 (447, 'getauid'),
                 (448, 'setauid'),
                 (449, 'getaudit'),
                 (450, 'setaudit'),
                 (451, 'getaudit_addr'),
                 (452, 'setaudit_addr'),
                 (453, 'auditctl'),
                 (455, 'thr_new'),
                 (457, 'kmq_open'),
                 (458, 'kmq_setattr'),
                 (459, 'kmq_timedreceive'),
                 (460, 'kmq_timedsend'),
                 (461, 'kmq_notify'),
                 (462, 'kmq_unlink'),
                 (463, 'abort2'),
                 (464, 'thr_set_name'),
                 (465, 'aio_fsync'),
                 (471, 'sctp_peeloff'),
                 (472, 'sctp_generic_sendmsg'),
                 (473, 'sctp_generic_sendmsg_iov'),
                 (474, 'sctp_generic_recvmsg'),
                 (481, 'thr_kill2'),
                 (484, 'cpuset'),
                 (485, 'cpuset_setid'),
                 (489, 'faccessat'),
                 (490, 'fchmodat'),
                 (491, 'fchownat'),
                 (492, 'fexecve'),
                 (493, 'fstatat'),
                 (494, 'futimesat'),
                 (495, 'linkat'),
                 (496, 'mkdirat'),
                 (497, 'mkfifoat'),
                 (498, 'mknodat'),
                 (499, 'openat'),
                 (500, 'readlinkat'),
                 (501, 'renameat'),
                 (502, 'symlinkat'),
                 (503, 'unlinkat'),
                 (504, 'posix_openpt'),
                 (505, 'gssd_syscall'),
                 (506, 'jail_get'),
                 (507, 'jail_set'),
                 (508, 'jail_remove'),
                 (509, 'closefrom'),
                 (510, 'semctl'),
                 (511, 'msgctl'),
                 (512, 'shmctl'),
                 (513, 'lpathconf'),
                 (515, '__cap_rights_get'),
                 (516, 'cap_enter'),
                 (517, 'cap_getmode'),
                 (518, 'pdfork'),
                 (519, 'pdkill'),
                 (520, 'pdgetpid'),
                 (523, 'getloginclass'),
                 (524, 'setloginclass'),
                 (525, 'rctl_get_racct'),
                 (526, 'rctl_get_rules'),
                 (527, 'rctl_get_limits'),
                 (528, 'rctl_add_rule'),
                 (529, 'rctl_remove_rule'),
                 (530, 'posix_fallocate'),
                 (531, 'posix_fadvise'),
                 (532, 'wait6'),
                 (533, 'cap_rights_limit'),
                 (534, 'cap_ioctls_limit'),
                 (535, 'cap_ioctls_get'),
                 (536, 'cap_fcntls_limit'),
                 (537, 'cap_fcntls_get'),
                 (538, 'bindat'),
                 (539, 'connectat'),
                 (540, 'chflagsat'),
                 (541, 'accept4'),
                 (542, 'pipe2'),
                 (543, 'aio_mlock'),
                 (544, 'procctl'),
                 (545, 'ppoll'),
                 (546, 'futimens'),
                 (547, 'utimensat'),
                 (548, 'numa_getaffinity'),
                 (549, 'numa_setaffinity')]

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

for no, name in missing_funcs:
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
