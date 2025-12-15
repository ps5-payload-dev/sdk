/* Copyright (C) 2023 John Törnblom

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

#include <sys/cdefs.h>
#include <sys/types.h>

__BEGIN_DECLS

// Absolute kernel pointers
extern const intptr_t KERNEL_ADDRESS_TEXT_BASE;
extern const intptr_t KERNEL_ADDRESS_DATA_BASE;
extern const intptr_t KERNEL_ADDRESS_ALLPROC;
extern const intptr_t KERNEL_ADDRESS_PRISON0;
extern const intptr_t KERNEL_ADDRESS_ROOTVNODE;
extern const intptr_t KERNEL_ADDRESS_SECURITY_FLAGS;
extern const intptr_t KERNEL_ADDRESS_UTOKEN_FLAGS;
extern const intptr_t KERNEL_ADDRESS_QA_FLAGS;
extern const intptr_t KERNEL_ADDRESS_TARGETID;
extern const intptr_t KERNEL_ADDRESS_BUS_DATA_DEVICES;

// Proc field offsets
extern const off_t KERNEL_OFFSET_PROC_P_UCRED;
extern const off_t KERNEL_OFFSET_PROC_P_FD;
extern const off_t KERNEL_OFFSET_PROC_P_PID;
extern const off_t KERNEL_OFFSET_PROC_P_VMSPACE;

// Ucred field offsets
extern const off_t KERNEL_OFFSET_UCRED_CR_UID;
extern const off_t KERNEL_OFFSET_UCRED_CR_RUID;
extern const off_t KERNEL_OFFSET_UCRED_CR_SVUID;
extern const off_t KERNEL_OFFSET_UCRED_CR_RGID;
extern const off_t KERNEL_OFFSET_UCRED_CR_SCEAUTHID;
extern const off_t KERNEL_OFFSET_UCRED_CR_SCECAPS;
extern const off_t KERNEL_OFFSET_UCRED_CR_SCEATTRS;

// Filedesc field offsets
extern const off_t KERNEL_OFFSET_FILEDESC_FD_RDIR;
extern const off_t KERNEL_OFFSET_FILEDESC_FD_JDIR;


uint32_t kernel_get_fw_version(void);

int32_t  kernel_copyin(const void *udaddr, intptr_t kaddr, size_t len);
int32_t  kernel_copyout(intptr_t kaddr, void *udaddr, size_t  len);

int32_t kernel_setlong(intptr_t addr, uint64_t val);
int32_t kernel_setint(intptr_t addr, uint32_t val);
int32_t kernel_setshort(intptr_t addr, uint16_t val);
int32_t kernel_setchar(intptr_t addr, uint8_t val);

uint64_t kernel_getlong(intptr_t addr);
uint32_t kernel_getint(intptr_t addr);
uint16_t kernel_getshort(intptr_t addr);
uint8_t  kernel_getchar(intptr_t addr);

intptr_t kernel_get_proc(pid_t pid);
intptr_t kernel_get_proc_thread(pid_t pid, pid_t tid);
intptr_t kernel_get_proc_ucred(pid_t pid);
intptr_t kernel_get_proc_filedesc(pid_t pid);
intptr_t kernel_get_proc_file(pid_t pid, int fd);

int kernel_get_vmem_protection(pid_t pid, intptr_t addr, size_t len);
int kernel_set_vmem_protection(pid_t pid, intptr_t addr, size_t len, int prot);
int kernel_mprotect(pid_t pid, intptr_t addr, size_t size, int prot);

int kernel_overlap_sockets(pid_t pid, int master_sock, int victim_sock);

int kernel_dynlib_handle(pid_t pid, const char* basename, uint32_t *handle);
intptr_t kernel_dynlib_dlsym(pid_t pid, uint32_t handle, const char *sym);
intptr_t kernel_dynlib_resolve(pid_t pid, uint32_t handle, const char *nid);
intptr_t kernel_dynlib_mapbase_addr(pid_t pid, uint32_t handle);
intptr_t kernel_dynlib_entry_addr(pid_t pid, uint32_t handle);
intptr_t kernel_dynlib_init_addr(pid_t pid, uint32_t handle);
intptr_t kernel_dynlib_fini_addr(pid_t pid, uint32_t handle);

uint64_t kernel_get_ucred_authid(pid_t pid);
int32_t  kernel_set_ucred_authid(pid_t pid, uint64_t authid);

int32_t kernel_get_ucred_caps(pid_t pid, uint8_t caps[16]);
int32_t kernel_set_ucred_caps(pid_t pid, const uint8_t caps[16]);

uint64_t kernel_get_ucred_attrs(pid_t pid);
int32_t  kernel_set_ucred_attrs(pid_t pid, uint64_t attr);

int32_t kernel_get_qaflags(uint8_t qaflags[16]);
int32_t kernel_set_qaflags(uint8_t const qaflags[16]);

intptr_t kernel_get_root_vnode(void);

intptr_t kernel_get_proc_rootdir(pid_t pid);
int32_t  kernel_set_proc_rootdir(pid_t pid, intptr_t vnode);

intptr_t kernel_get_proc_jaildir(pid_t pid);
int32_t  kernel_set_proc_jaildir(pid_t pid, intptr_t vnode);

uid_t   kernel_get_ucred_uid(pid_t pid);
int32_t kernel_set_ucred_uid(pid_t pid, uid_t uid);

uid_t   kernel_get_ucred_ruid(pid_t pid);
int32_t kernel_set_ucred_ruid(pid_t pid, uid_t ruid);

uid_t   kernel_get_ucred_svuid(pid_t pid);
int32_t kernel_set_ucred_svuid(pid_t pid, uid_t svuid);

gid_t   kernel_get_ucred_rgid(pid_t pid);
int32_t kernel_set_ucred_rgid(pid_t pid, gid_t rgid);

gid_t   kernel_get_ucred_svgid(pid_t pid);
int32_t kernel_set_ucred_svgid(pid_t pid, gid_t svgid);

__END_DECLS

