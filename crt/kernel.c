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

#include "elf.h"
#include "kernel.h"
#include "nid.h"
#include "syscall.h"


/**
 * standard macros.
 **/
#define IPPROTO_IPV6 41
#define IPV6_PKTINFO 46

#define EBADF  9
#define EFAULT 14
#define ENOSYS 78


/**
 * public constants.
 **/
unsigned long KERNEL_ADDRESS_TEXT_BASE      = 0;
unsigned long KERNEL_ADDRESS_DATA_BASE      = 0;
unsigned long KERNEL_ADDRESS_ALLPROC        = 0;
unsigned long KERNEL_ADDRESS_PRISON0        = 0;
unsigned long KERNEL_ADDRESS_ROOTVNODE      = 0;
unsigned long KERNEL_ADDRESS_SECURITY_FLAGS = 0;
unsigned long KERNEL_ADDRESS_UTOKEN_FLAGS   = 0;
unsigned long KERNEL_ADDRESS_QA_FLAGS       = 0;
unsigned long KERNEL_ADDRESS_TARGETID       = 0;

const unsigned long KERNEL_OFFSET_PROC_P_UCRED   = 0x40;
const unsigned long KERNEL_OFFSET_PROC_P_FD      = 0x48;
const unsigned long KERNEL_OFFSET_PROC_P_PID     = 0xBC;
const unsigned long KERNEL_OFFSET_PROC_P_VMSPACE = 0x200;

unsigned long KERNEL_OFFSET_VMSPACE_P_ROOT = 0;

const unsigned long KERNEL_OFFSET_UCRED_CR_UID   = 0x04;
const unsigned long KERNEL_OFFSET_UCRED_CR_RUID  = 0x08;
const unsigned long KERNEL_OFFSET_UCRED_CR_SVUID = 0x0C;
const unsigned long KERNEL_OFFSET_UCRED_CR_RGID  = 0x14;
const unsigned long KERNEL_OFFSET_UCRED_CR_SVGID = 0x18;

const unsigned long KERNEL_OFFSET_UCRED_CR_SCEAUTHID = 0x58;
const unsigned long KERNEL_OFFSET_UCRED_CR_SCECAPS   = 0x60;
const unsigned long KERNEL_OFFSET_UCRED_CR_SCEATTRS  = 0x83;

const unsigned long KERNEL_OFFSET_FILEDESC_FD_RDIR = 0x10;
const unsigned long KERNEL_OFFSET_FILEDESC_FD_JDIR = 0x18;


/**
 * private global variables.
 **/
static unsigned long pipe_addr = 0;
static int rw_pipe[2] = {-1, -1};
static int rw_pair[2] = {-1, -1};

#define MASTER_SOCK rw_pair[0]
#define VICTIM_SOCK rw_pair[1]


/**
 * we need strcmp() before we can resolve symbols.
 **/
static int
strncmp(const char *s1, const char *s2, unsigned long n) {
  if(n == 0) {
    return 0;
  }

  do {
    if(*s1 != *s2++) {
      return (*(const unsigned char *)s1 -
              *(const unsigned char *)(s2 - 1));
    }
    if(*s1++ == '\0') {
      break;
    }
  } while (--n != 0);

  return 0;
}


/**
 * we need strlen() before we can resolve symbols.
 **/
static unsigned long
strlen(const char *str) {
  const char *start = str;

  while(*str) {
    str++;
  }

  return str - start;
}


unsigned int
kernel_get_fw_version(void) {
  int mib[2] = {1, 46};
  unsigned long size = sizeof(mib);
  unsigned int version = 0;

  if(__syscall(SYS_sysctl, mib, 2, &version, &size, 0, 0)) {
    return 0;
  }

  return version;
}


int
__kernel_init(payload_args_t* args) {
  if((rw_pair[0]=args->rwpair[0]) < 0) {
    return -EBADF;
  }
  if((rw_pair[1]=args->rwpair[1]) < 0) {
    return -EBADF;
  }

  if((rw_pipe[0]=args->rwpipe[0]) < 0) {
    return -EBADF;
  }
  if((rw_pipe[1]=args->rwpipe[1]) < 0) {
    return -EBADF;
  }

  if(!(pipe_addr=args->kpipe_addr)) {
    return -EFAULT;
  }
  if(!(KERNEL_ADDRESS_DATA_BASE=args->kdata_base_addr)) {
    return -EFAULT;
  }

  switch(kernel_get_fw_version() & 0xffff0000) {
  case 0x1000000:
  case 0x1010000:
  case 0x1020000:
    KERNEL_ADDRESS_TEXT_BASE      = KERNEL_ADDRESS_DATA_BASE - 0x1B40000;
    KERNEL_ADDRESS_ALLPROC        = KERNEL_ADDRESS_DATA_BASE + 0x26D1BF8;
    KERNEL_ADDRESS_SECURITY_FLAGS = KERNEL_ADDRESS_DATA_BASE + 0x6241074;
    KERNEL_ADDRESS_TARGETID       = KERNEL_ADDRESS_DATA_BASE + 0x624107D;
    KERNEL_ADDRESS_QA_FLAGS       = KERNEL_ADDRESS_DATA_BASE + 0x6241098;
    KERNEL_ADDRESS_UTOKEN_FLAGS   = KERNEL_ADDRESS_DATA_BASE + 0x6241100;
    KERNEL_ADDRESS_PRISON0        = KERNEL_ADDRESS_DATA_BASE + 0x1911E00;
    KERNEL_ADDRESS_ROOTVNODE      = KERNEL_ADDRESS_DATA_BASE + 0x6565540;
    KERNEL_OFFSET_VMSPACE_P_ROOT  = 0x1c8;
    break;

  case 0x1050000:
  case 0x1100000:
  case 0x1110000:
  case 0x1120000:
  case 0x1130000:
  case 0x1140000:
    KERNEL_ADDRESS_TEXT_BASE      = KERNEL_ADDRESS_DATA_BASE - 0x1B40000;
    KERNEL_ADDRESS_ALLPROC        = KERNEL_ADDRESS_DATA_BASE + 0x26D1C18;
    KERNEL_ADDRESS_SECURITY_FLAGS = KERNEL_ADDRESS_DATA_BASE + 0x6241074;
    KERNEL_ADDRESS_TARGETID       = KERNEL_ADDRESS_DATA_BASE + 0x624107D;
    KERNEL_ADDRESS_QA_FLAGS       = KERNEL_ADDRESS_DATA_BASE + 0x6241098;
    KERNEL_ADDRESS_UTOKEN_FLAGS   = KERNEL_ADDRESS_DATA_BASE + 0x6241100;
    KERNEL_ADDRESS_PRISON0        = KERNEL_ADDRESS_DATA_BASE + 0x1911E00;
    KERNEL_ADDRESS_ROOTVNODE      = KERNEL_ADDRESS_DATA_BASE + 0x6565540;
    KERNEL_OFFSET_VMSPACE_P_ROOT  = 0x1c8;
    break;

  case 0x2000000:
    KERNEL_ADDRESS_TEXT_BASE      = KERNEL_ADDRESS_DATA_BASE - 0x1B80000;
    KERNEL_ADDRESS_ALLPROC        = KERNEL_ADDRESS_DATA_BASE + 0x2701C28;
    KERNEL_ADDRESS_SECURITY_FLAGS = KERNEL_ADDRESS_DATA_BASE + 0x63E1274;
    KERNEL_ADDRESS_TARGETID       = KERNEL_ADDRESS_DATA_BASE + 0x63E127D;
    KERNEL_ADDRESS_QA_FLAGS       = KERNEL_ADDRESS_DATA_BASE + 0x63E1298;
    KERNEL_ADDRESS_UTOKEN_FLAGS   = KERNEL_ADDRESS_DATA_BASE + 0x63E1300;
    KERNEL_ADDRESS_PRISON0        = KERNEL_ADDRESS_DATA_BASE + 0x194BA60;
    KERNEL_ADDRESS_ROOTVNODE      = KERNEL_ADDRESS_DATA_BASE + 0x67134C0;
    KERNEL_OFFSET_VMSPACE_P_ROOT  = 0x1c8;
    break;

  case 0x2200000:
  case 0x2250000:
  case 0x2260000:
  case 0x2300000:
  case 0x2500000:
  case 0x2700000:
    KERNEL_ADDRESS_TEXT_BASE      = KERNEL_ADDRESS_DATA_BASE - 0x1B80000;
    KERNEL_ADDRESS_ALLPROC        = KERNEL_ADDRESS_DATA_BASE + 0x2701C28;
    KERNEL_ADDRESS_SECURITY_FLAGS = KERNEL_ADDRESS_DATA_BASE + 0x63E1274;
    KERNEL_ADDRESS_TARGETID       = KERNEL_ADDRESS_DATA_BASE + 0x63E127D;
    KERNEL_ADDRESS_QA_FLAGS       = KERNEL_ADDRESS_DATA_BASE + 0x63E1298;
    KERNEL_ADDRESS_UTOKEN_FLAGS   = KERNEL_ADDRESS_DATA_BASE + 0x63E1300;
    KERNEL_ADDRESS_PRISON0        = KERNEL_ADDRESS_DATA_BASE + 0x194BD20;
    KERNEL_ADDRESS_ROOTVNODE      = KERNEL_ADDRESS_DATA_BASE + 0x67134C0;
    KERNEL_OFFSET_VMSPACE_P_ROOT  = 0x1c8;
    break;

  case 0x3000000:
  case 0x3100000:
  case 0x3200000:
  case 0x3210000:
    KERNEL_ADDRESS_TEXT_BASE      = KERNEL_ADDRESS_DATA_BASE - 0x0BD0000;
    KERNEL_ADDRESS_ALLPROC        = KERNEL_ADDRESS_DATA_BASE + 0x276DC58;
    KERNEL_ADDRESS_SECURITY_FLAGS = KERNEL_ADDRESS_DATA_BASE + 0x6466474;
    KERNEL_ADDRESS_TARGETID       = KERNEL_ADDRESS_DATA_BASE + 0x646647D;
    KERNEL_ADDRESS_QA_FLAGS       = KERNEL_ADDRESS_DATA_BASE + 0x6466498;
    KERNEL_ADDRESS_UTOKEN_FLAGS   = KERNEL_ADDRESS_DATA_BASE + 0x6466500;
    KERNEL_ADDRESS_PRISON0        = KERNEL_ADDRESS_DATA_BASE + 0x1CC2670;
    KERNEL_ADDRESS_ROOTVNODE      = KERNEL_ADDRESS_DATA_BASE + 0x67AB4C0;
    KERNEL_OFFSET_VMSPACE_P_ROOT  = 0x1c8;
    break;

  case 0x4020000:
    KERNEL_ADDRESS_TEXT_BASE      = KERNEL_ADDRESS_DATA_BASE - 0x0C00000;
    KERNEL_ADDRESS_ALLPROC        = KERNEL_ADDRESS_DATA_BASE + 0x27EDCB8;
    KERNEL_ADDRESS_SECURITY_FLAGS = KERNEL_ADDRESS_DATA_BASE + 0x6506474;
    KERNEL_ADDRESS_TARGETID       = KERNEL_ADDRESS_DATA_BASE + 0x650647D;
    KERNEL_ADDRESS_QA_FLAGS       = KERNEL_ADDRESS_DATA_BASE + 0x6506498;
    KERNEL_ADDRESS_UTOKEN_FLAGS   = KERNEL_ADDRESS_DATA_BASE + 0x6506500;
    KERNEL_ADDRESS_PRISON0        = KERNEL_ADDRESS_DATA_BASE + 0x1D34D00;
    KERNEL_ADDRESS_ROOTVNODE      = KERNEL_ADDRESS_DATA_BASE + 0x66E74C0;
    KERNEL_OFFSET_VMSPACE_P_ROOT  = 0x1c8;
    break;

  case 0x4000000:
  case 0x4030000:
  case 0x4500000:
  case 0x4510000:
    KERNEL_ADDRESS_TEXT_BASE      = KERNEL_ADDRESS_DATA_BASE - 0x0C00000;
    KERNEL_ADDRESS_ALLPROC        = KERNEL_ADDRESS_DATA_BASE + 0x27EDCB8;
    KERNEL_ADDRESS_SECURITY_FLAGS = KERNEL_ADDRESS_DATA_BASE + 0x6506474;
    KERNEL_ADDRESS_TARGETID       = KERNEL_ADDRESS_DATA_BASE + 0x650647D;
    KERNEL_ADDRESS_QA_FLAGS       = KERNEL_ADDRESS_DATA_BASE + 0x6506498;
    KERNEL_ADDRESS_UTOKEN_FLAGS   = KERNEL_ADDRESS_DATA_BASE + 0x6506500;
    KERNEL_ADDRESS_PRISON0        = KERNEL_ADDRESS_DATA_BASE + 0x1D34D00;
    KERNEL_ADDRESS_ROOTVNODE      = KERNEL_ADDRESS_DATA_BASE + 0x66E74C0;
    KERNEL_OFFSET_VMSPACE_P_ROOT  = 0x1c8;
    break;

  case 0x5000000:
  case 0x5020000:
  case 0x5100000:
  case 0x5500000:
    KERNEL_ADDRESS_TEXT_BASE      = KERNEL_ADDRESS_DATA_BASE - 0x0C40000;
    KERNEL_ADDRESS_ALLPROC        = KERNEL_ADDRESS_DATA_BASE + 0x291DD00;
    KERNEL_ADDRESS_SECURITY_FLAGS = KERNEL_ADDRESS_DATA_BASE + 0x66466EC;
    KERNEL_ADDRESS_TARGETID       = KERNEL_ADDRESS_DATA_BASE + 0x66466F5;
    KERNEL_ADDRESS_QA_FLAGS       = KERNEL_ADDRESS_DATA_BASE + 0x6646710;
    KERNEL_ADDRESS_UTOKEN_FLAGS   = KERNEL_ADDRESS_DATA_BASE + 0x6646778;
    KERNEL_ADDRESS_PRISON0        = KERNEL_ADDRESS_DATA_BASE + 0x1E23470;
    KERNEL_ADDRESS_ROOTVNODE      = KERNEL_ADDRESS_DATA_BASE + 0x6853510;
    KERNEL_OFFSET_VMSPACE_P_ROOT  = 0x1c8;
    break;

  case 0x6000000:
  case 0x6020000:
  case 0x6500000:
    KERNEL_ADDRESS_TEXT_BASE      = KERNEL_ADDRESS_DATA_BASE - 0x0C60000;
    KERNEL_ADDRESS_ALLPROC        = KERNEL_ADDRESS_DATA_BASE + 0x2869D20;
    KERNEL_ADDRESS_SECURITY_FLAGS = KERNEL_ADDRESS_DATA_BASE + 0x65968EC;
    KERNEL_ADDRESS_TARGETID       = KERNEL_ADDRESS_DATA_BASE + 0x65968EC + 0x09;
    KERNEL_ADDRESS_QA_FLAGS       = KERNEL_ADDRESS_DATA_BASE + 0x65968EC + 0x24;
    KERNEL_ADDRESS_UTOKEN_FLAGS   = KERNEL_ADDRESS_DATA_BASE + 0x65968EC + 0x8C;
    KERNEL_ADDRESS_PRISON0        = KERNEL_ADDRESS_DATA_BASE + 0x1E45560;
    KERNEL_ADDRESS_ROOTVNODE      = KERNEL_ADDRESS_DATA_BASE + 0x679F510;
    KERNEL_OFFSET_VMSPACE_P_ROOT  = 0x1c8; //TODO: confirm offset
    break;

  case 0x7000000:
  case 0x7010000:
  case 0x7200000:
  case 0x7400000:
  case 0x7600000:
  case 0x7610000:
    KERNEL_ADDRESS_TEXT_BASE      = KERNEL_ADDRESS_DATA_BASE - 0x0C50000;
    KERNEL_ADDRESS_ALLPROC        = KERNEL_ADDRESS_DATA_BASE + 0x2859D50;
    KERNEL_ADDRESS_SECURITY_FLAGS = KERNEL_ADDRESS_DATA_BASE + 0x0AC8064;
    KERNEL_ADDRESS_TARGETID       = KERNEL_ADDRESS_DATA_BASE + 0x0AC8064 + 0x09;
    KERNEL_ADDRESS_QA_FLAGS       = KERNEL_ADDRESS_DATA_BASE + 0x0AC8064 + 0x24;
    KERNEL_ADDRESS_UTOKEN_FLAGS   = KERNEL_ADDRESS_DATA_BASE + 0x0AC8064 + 0x8C;
    KERNEL_ADDRESS_PRISON0        = KERNEL_ADDRESS_DATA_BASE + 0x1E477F0;
    KERNEL_ADDRESS_ROOTVNODE      = KERNEL_ADDRESS_DATA_BASE + 0x30C7510;
    KERNEL_OFFSET_VMSPACE_P_ROOT  = 0x1d0;
    break;

  default:
    return -ENOSYS;
  }

  return 0;
}


/**
 * Write data to an address in kernel space.
 **/
static int
kernel_write(unsigned long addr, unsigned long *data) {
  unsigned long victim_buf[3];

  // sanity check for invalid kernel pointers
  if(!(addr & 0xffff000000000000)) {
    return -1;
  }

  victim_buf[0] = addr;
  victim_buf[1] = 0;
  victim_buf[2] = 0;

  if(__syscall(SYS_setsockopt, MASTER_SOCK, IPPROTO_IPV6, IPV6_PKTINFO,
	       victim_buf, 0x14)) {
    return -1;
  }

  if(__syscall(SYS_setsockopt, VICTIM_SOCK, IPPROTO_IPV6, IPV6_PKTINFO,
	       data, 0x14)) {
    return -1;
  }

  return 0;
}


int
kernel_copyin(const void *uaddr, unsigned long kaddr, unsigned long len) {
  unsigned long write_buf[3];

  if(!kaddr || !uaddr || !len) {
    return -1;
  }

  // Set pipe flags
  write_buf[0] = 0;
  write_buf[1] = 0x4000000000000000;
  write_buf[2] = 0;
  if(kernel_write(pipe_addr, (unsigned long *) &write_buf)) {
    return -1;
  }

  // Set pipe data addr
  write_buf[0] = kaddr;
  write_buf[1] = 0;
  write_buf[2] = 0;
  if(kernel_write(pipe_addr + 0x10, (unsigned long *) &write_buf)) {
    return -1;
  }

  // Perform write across pipe
  if(__syscall(SYS_write, rw_pipe[1], uaddr, len) < 0) {
    return -1;
  }

  return 0;
}


int
kernel_copyout(unsigned long kaddr, void *uaddr, unsigned long len) {
  unsigned long write_buf[3];

  if(!kaddr || !uaddr || !len) {
    return -1;
  }

  // Set pipe flags
  write_buf[0] = 0x4000000040000000;
  write_buf[1] = 0x4000000000000000;
  write_buf[2] = 0;
  if(kernel_write(pipe_addr, (unsigned long *) &write_buf)) {
    return -1;
  }

  // Set pipe data addr
  write_buf[0] = kaddr;
  write_buf[1] = 0;
  write_buf[2] = 0;
  if(kernel_write(pipe_addr + 0x10, (unsigned long *) &write_buf)) {
    return -1;
  }

  // Perform read across pipe
  if(__syscall(SYS_read, rw_pipe[0], uaddr, len) < 0) {
    return -1;
  }

  return 0;
}

int
kernel_setlong(unsigned long addr, unsigned long val) {
  return kernel_copyin(&val, addr, sizeof(val));
}

int
kernel_setint(unsigned long addr, unsigned int val) {
  return kernel_copyin(&val, addr, sizeof(val));
}

int
kernel_setshort(unsigned long addr, unsigned short val) {
  return kernel_copyin(&val, addr, sizeof(val));
}

int
kernel_setchar(unsigned long addr, unsigned char val) {
  return kernel_copyin(&val, addr, sizeof(val));
}

unsigned long
kernel_getlong(unsigned long addr) {
  unsigned long val = 0;

  kernel_copyout(addr, &val, sizeof(val));

  return val;
}

unsigned int
kernel_getint(unsigned long addr) {
  unsigned int val = 0;

  kernel_copyout(addr, &val, sizeof(val));

  return val;
}

unsigned short
kernel_getshort(unsigned long addr) {
  unsigned short val = 0;

  kernel_copyout(addr, &val, sizeof(val));

  return val;
}

unsigned char
kernel_getchar(unsigned long addr) {
  unsigned char val = 0;

  kernel_copyout(addr, &val, sizeof(val));

  return val;
}

int
kernel_get_qaflags(unsigned char qaflags[16]) {
  return kernel_copyout(KERNEL_ADDRESS_QA_FLAGS, qaflags, 16);
}


int
kernel_set_qaflags(const unsigned char qaflags[16]) {
  if(kernel_get_fw_version() < 0x7000000) {
    return kernel_copyin(qaflags, KERNEL_ADDRESS_QA_FLAGS, 16);
  } else {
    return -ENOSYS; // currently not supported
  }
}


unsigned long
kernel_get_root_vnode(void) {
  unsigned long vnode = 0;

  if(kernel_copyout(KERNEL_ADDRESS_ROOTVNODE, &vnode, sizeof(vnode))) {
    return 0;
  }

  return vnode;
}


unsigned long
kernel_get_proc(int pid) {
  unsigned int other_pid = 0;
  unsigned long addr = 0;
  unsigned long next = 0;

  if(kernel_copyout(KERNEL_ADDRESS_ALLPROC, &addr, sizeof(addr))) {
    return 0;
  }

  if(pid <= 0) {
    pid = __syscall(SYS_getpid);
  }

  while(addr) {
    if(kernel_copyout(addr + KERNEL_OFFSET_PROC_P_PID, &other_pid,
		      sizeof(other_pid))) {
      return 0;
    }

    if(pid == other_pid) {
      break;
    }

    if(kernel_copyout(addr, &next, sizeof(next))) {
      return 0;
    }

    addr = next;
  }

  return addr;
}


int
kernel_dynlib_obj(int pid, unsigned int handle, dynlib_obj_t* obj) {
  unsigned long kproc;
  unsigned long kaddr;

  if(!(kproc=kernel_get_proc(pid))) {
    return -1;
  }

  if(kernel_copyout(kproc + 0x3e8, &kaddr, sizeof(kaddr)) < 0) {
    return -1;
  }

  do {
    if(kernel_copyout(kaddr, &kaddr, sizeof(kaddr)) < 0) {
      return -1;
    }
    if(!kaddr) {
      return -1;
    }

    if(kernel_copyout(kaddr + __builtin_offsetof(dynlib_obj_t, handle),
		      &obj->handle, sizeof(obj->handle)) < 0) {
      return -1;
    }
  } while(obj->handle != handle);

  if(kernel_copyout(kaddr, obj, sizeof(dynlib_obj_t)) < 0) {
    return -1;
  }

  return 0;
}


int
kernel_dynlib_find_handle(int pid, unsigned long addr, unsigned int* handle) {
  unsigned long mapbase;
  unsigned long mapsize;
  unsigned long kproc;
  unsigned long kaddr;
  unsigned long h;

  if(!(kproc=kernel_get_proc(pid))) {
    return -1;
  }

  if(kernel_copyout(kproc + 0x3e8, &kaddr, sizeof(kaddr)) < 0) {
    return -1;
  }

  while(1) {
    if(kernel_copyout(kaddr, &kaddr, sizeof(kaddr)) < 0) {
      return -1;
    }
    if(!kaddr) {
      return -1;
    }

    if(kernel_copyout(kaddr + __builtin_offsetof(dynlib_obj_t, mapbase),
		      &mapbase, sizeof(mapbase)) < 0) {
      return -1;
    }

    if(kernel_copyout(kaddr + __builtin_offsetof(dynlib_obj_t, mapsize),
		      &mapsize, sizeof(mapsize)) < 0) {
      return -1;
    }

    if(mapbase <= addr && addr <= mapbase + mapsize) {
      if(kernel_copyout(kaddr + __builtin_offsetof(dynlib_obj_t, handle),
                        &h, sizeof(h)) < 0) {
        return -1;
      }
      *handle = (unsigned int)h;
      return 0;
    }
  }

  return -1;
}


int
kernel_dynlib_handle(int pid, const char* basename, unsigned int *handle) {
  unsigned long kproc;
  unsigned long kaddr;
  unsigned long kpath;
  unsigned long blen;
  unsigned long plen;
  char path[1024];
  long temphandle;

  if(!(kproc=kernel_get_proc(pid))) {
    return -1;
  }

  if(kernel_copyout(kproc + 0x3e8, &kaddr, sizeof(kaddr)) < 0) {
    return -1;
  }

  blen = strlen(basename);
  do {
    if(kernel_copyout(kaddr, &kaddr, sizeof(kaddr)) < 0) {
      return -1;
    }
    if(!kaddr) {
      return -1;
    }
    if(kernel_copyout(kaddr + __builtin_offsetof(dynlib_obj_t, path),
		      &kpath, sizeof(kpath)) < 0) {
      return -1;
    }
    if(kernel_copyout(kpath, path, sizeof(path)) < 0) {
      return -1;
    }

    if(kernel_copyout(kaddr + __builtin_offsetof(dynlib_obj_t, handle),
		      &temphandle, sizeof(temphandle)) < 0) {
      return -1;
    }

    plen = strlen(path);
    if(plen <= blen) {
      continue;
    }
    if(path[plen-blen-1] != '/') {
      continue;
    }
    if(strncmp(path + plen - blen, basename, blen)) {
      continue;
    }

    *handle = (unsigned int)temphandle;
    return 0;

  } while(1);
}


unsigned long
kernel_dynlib_fini_addr(int pid, unsigned int handle) {
  dynlib_obj_t obj;

  if(kernel_dynlib_obj(pid, handle, &obj)) {
    return 0;
  }

  return obj.fini;
}


int
kernel_dynlib_path(int pid, unsigned int handle, char* path, unsigned long size) {
  dynlib_obj_t obj;

  if(size > 1024) {
    size = 1024;
  }
  if(kernel_dynlib_obj(pid, handle, &obj)) {
    return -1;
  }
  if(kernel_copyout(obj.path, path, size) < 0) {
    return -1;
  }

  path[size-1] = 0;

  return 0;
}


unsigned long
kernel_dynlib_init_addr(int pid, unsigned int handle) {
  dynlib_obj_t obj;

  if(kernel_dynlib_obj(pid, handle, &obj)) {
    return 0;
  }

  return obj.init;
}


unsigned long
kernel_dynlib_entry_addr(int pid, unsigned int handle) {
  dynlib_obj_t obj;

  if(kernel_dynlib_obj(pid, handle, &obj)) {
    return 0;
  }

  return obj.entry;
}


unsigned long
kernel_dynlib_mapbase_addr(int pid, unsigned int handle) {
  dynlib_obj_t obj;

  if(kernel_dynlib_obj(pid, handle, &obj)) {
    return 0;
  }

  return obj.mapbase;
}


unsigned long
kernel_dynlib_resolve(int pid, int handle, const char *nid) {
  unsigned long vaddr = 0;
  dynlib_dynsec_t dynsec;
  dynlib_obj_t obj;
  Elf64_Sym sym;
  char str[12];

  if(kernel_dynlib_obj(pid, handle, &obj)) {
    return 0;
  }

  if(kernel_copyout(obj.dynsec, &dynsec, sizeof(dynsec)) < 0) {
    return 0;
  }

  for(unsigned long i=0; i<dynsec.symtabsize / sizeof(sym); i++) {
    if(kernel_copyout(dynsec.symtab + sizeof(sym)*i, &sym, sizeof(sym)) < 0) {
      return 0;
    }
    if(!sym.st_value) {
      continue;
    }
    if(kernel_copyout(dynsec.strtab + sym.st_name, str, sizeof(str)) < 0) {
      return 0;
    }
    if(!strncmp(nid, str, 11)) {
      vaddr = obj.mapbase + sym.st_value;
      break;
    }
  }

  return vaddr;
}


unsigned long
kernel_dynlib_dlsym(int pid, unsigned int handle, const char* sym) {
  char nid[12];

  nid_encode(sym, nid);

  return kernel_dynlib_resolve(pid, handle, nid);
}


unsigned long
kernel_get_proc_ucred(int pid) {
  unsigned long proc = 0;
  unsigned long ucred = 0;

  if(!(proc=kernel_get_proc(pid))) {
    return 0;
  }

  if(kernel_copyout(proc + KERNEL_OFFSET_PROC_P_UCRED, &ucred,
		    sizeof(ucred))) {
    return 0;
  }

  return ucred;
}


unsigned long
kernel_get_ucred_authid(int pid) {
  unsigned long authid = 0;
  unsigned long ucred = 0;

  if(!(ucred=kernel_get_proc_ucred(pid))) {
    return 0;
  }

  if(kernel_copyout(ucred + KERNEL_OFFSET_UCRED_CR_SCEAUTHID, &authid,
		    sizeof(authid))) {
    return 0;
  }

  return authid;
}


int
kernel_set_ucred_authid(int pid, unsigned long authid) {
  unsigned long ucred = 0;

  if(!(ucred=kernel_get_proc_ucred(pid))) {
    return -1;
  }

  if(kernel_copyin(&authid, ucred + KERNEL_OFFSET_UCRED_CR_SCEAUTHID,
		   sizeof(authid))) {
    return -1;
  }

  return 0;
}


int
kernel_get_ucred_caps(int pid, unsigned char caps[16]) {
  unsigned long ucred = 0;

  if(!(ucred=kernel_get_proc_ucred(pid))) {
    return -1;
  }

  if(kernel_copyout(ucred + KERNEL_OFFSET_UCRED_CR_SCECAPS, caps, 16)) {
    return -1;
  }

  return 0;
}


int
kernel_set_ucred_caps(int pid, const unsigned char caps[16]) {
  unsigned long ucred = 0;

  if(!(ucred=kernel_get_proc_ucred(pid))) {
    return -1;
  }

  if(kernel_copyin(caps, ucred + KERNEL_OFFSET_UCRED_CR_SCECAPS, 16)) {
    return -1;
  }

  return 0;
}


unsigned long
kernel_get_ucred_attrs(int pid) {
  unsigned long ucred = 0;
  unsigned long attrs = 0;

  if(!(ucred=kernel_get_proc_ucred(pid))) {
    return 0;
  }

  if(kernel_copyout(ucred + KERNEL_OFFSET_UCRED_CR_SCEATTRS, &attrs,
		    sizeof(attrs))) {
    return 0;
  }

  return attrs;
}


int
kernel_set_ucred_attrs(int pid, unsigned long attrs) {
  unsigned long ucred = 0;

  if(!(ucred=kernel_get_proc_ucred(pid))) {
    return -1;
  }

  if(kernel_copyin(&attrs, ucred + KERNEL_OFFSET_UCRED_CR_SCEATTRS,
		   sizeof(attrs))) {
    return -1;
  }

  return 0;
}


int
kernel_set_ucred_uid(int pid, unsigned int uid) {
  unsigned long ucred = 0;

  if(!(ucred=kernel_get_proc_ucred(pid))) {
    return -1;
  }

  if(kernel_copyin(&uid, ucred + KERNEL_OFFSET_UCRED_CR_UID,
		   sizeof(uid))) {
    return -1;
  }

  return 0;
}


int
kernel_set_ucred_ruid(int pid, unsigned int ruid) {
  unsigned long ucred = 0;

  if(!(ucred=kernel_get_proc_ucred(pid))) {
    return -1;
  }

  if(kernel_copyin(&ruid, ucred + KERNEL_OFFSET_UCRED_CR_RUID,
		   sizeof(ruid))) {
    return -1;
  }

  return 0;
}


int
kernel_set_ucred_svuid(int pid, unsigned int svuid) {
  unsigned long ucred = 0;

  if(!(ucred=kernel_get_proc_ucred(pid))) {
    return -1;
  }

  if(kernel_copyin(&svuid, ucred + KERNEL_OFFSET_UCRED_CR_SVUID,
		   sizeof(svuid))) {
    return -1;
  }

  return 0;
}


int
kernel_set_ucred_rgid(int pid, unsigned int rgid) {
  unsigned long ucred = 0;

  if(!(ucred=kernel_get_proc_ucred(pid))) {
    return -1;
  }

  if(kernel_copyin(&rgid, ucred + KERNEL_OFFSET_UCRED_CR_RGID,
		   sizeof(rgid))) {
    return -1;
  }

  return 0;
}


int
kernel_set_ucred_svgid(int pid, unsigned int svgid) {
  unsigned long ucred = 0;

  if(!(ucred=kernel_get_proc_ucred(pid))) {
    return -1;
  }

  if(kernel_copyin(&svgid, ucred + KERNEL_OFFSET_UCRED_CR_SVGID,
		   sizeof(svgid))) {
    return -1;
  }

  return 0;
}


unsigned long
kernel_get_proc_filedesc(int pid) {
  unsigned long filedesc = 0;
  unsigned long proc = 0;

  if(!(proc=kernel_get_proc(pid))) {
    return 0;
  }

  if(kernel_copyout(proc + KERNEL_OFFSET_PROC_P_FD, &filedesc,
		    sizeof(filedesc))) {
    return 0;
  }

  return filedesc;
}


int
kernel_mprotect(int pid, unsigned long addr, unsigned long len, int prot) {
  unsigned long vm_map_entry_addr;
  unsigned long vmspace_addr;
  unsigned long proc_addr;
  unsigned char vm_prot;
  unsigned long start;
  unsigned long end;

  if(!(proc_addr=kernel_get_proc(pid))) {
    return -1;
  }

  if(kernel_copyout(proc_addr + KERNEL_OFFSET_PROC_P_VMSPACE,
                    &vmspace_addr, sizeof(vmspace_addr))) {
    return -1;
  }

  if(kernel_copyout(vmspace_addr + KERNEL_OFFSET_VMSPACE_P_ROOT,
		    &vm_map_entry_addr, sizeof(vm_map_entry_addr))) {
    return -1;
  }

  while(vm_map_entry_addr) {
    if(kernel_copyout(vm_map_entry_addr + 0x20, &start, sizeof(start))) {
      return -1;
    }
    if(kernel_copyout(vm_map_entry_addr + 0x28, &end, sizeof(end))) {
      return -1;
    } 

    if(addr < start) {
      // left
      if(kernel_copyout(vm_map_entry_addr + 0x10, &vm_map_entry_addr,
                        sizeof(vm_map_entry_addr))) {
        return -1;
      }
    } else if(addr >= end) {
      // right
      if(kernel_copyout(vm_map_entry_addr + 0x18, &vm_map_entry_addr,
                        sizeof(vm_map_entry_addr))) {
        return -1;
      }
    } else {
      // protection
      if(kernel_copyout(vm_map_entry_addr + 0x64, &vm_prot, sizeof(vm_prot))) {
        return -1;
      }
      vm_prot |= prot;
      if(kernel_copyin(&vm_prot, vm_map_entry_addr + 0x64, sizeof(vm_prot))) {
        return -1;
      }

      // max_protection
      if(kernel_copyout(vm_map_entry_addr + 0x65, &vm_prot, sizeof(vm_prot))) {
        return -1;
      }
      vm_prot |= prot;
      if(kernel_copyin(&vm_prot, vm_map_entry_addr + 0x65, sizeof(vm_prot))) {
        return -1;
      }

      return 0;
    }
  }

  return -1;
}


unsigned long
kernel_get_proc_file(int pid, int fd) {
  unsigned long fd_files;
  unsigned long fde_file;
  unsigned long file;
  unsigned long proc;
  unsigned long p_fd;

  if(!(proc=kernel_get_proc(pid))) {
    return 0;
  }

  if(kernel_copyout(proc + 0x48, &p_fd, sizeof(p_fd))) {
    return 0;
  }

  if(kernel_copyout(p_fd, &fd_files, sizeof(fd_files))) {
    return 0;
  }

  if(kernel_copyout(fd_files + 8 + (0x30 * fd),
		    &fde_file, sizeof(fde_file))) {
    return 0;
  }

  if(kernel_copyout(fde_file, &file, sizeof(file))) {
    return 0;
  }

  return file;
}


/**
 *
 **/
static unsigned long
kernel_get_proc_inp6_outputopts(int pid, int fd) {
  unsigned long inp6_outputopts;
  unsigned long so_pcb;
  unsigned long file;

  if(!(file=kernel_get_proc_file(pid, fd))) {
    return 0;
  }

  if(kernel_copyout(file + 0x18, &so_pcb, sizeof(so_pcb))) {
    return 0;
  }

  if(kernel_copyout(so_pcb + 0x120, &inp6_outputopts,
		    sizeof(inp6_outputopts))) {
    return 0;
  }

  return inp6_outputopts;
}


/**
 *
 **/
static int
kernel_inc_so_count(int pid, int fd) {
  unsigned long file;
  int so_count;

  if(!(file=kernel_get_proc_file(pid, fd))) {
    return -1;
  }

  if(kernel_copyout(file, &so_count, sizeof(so_count))) {
    return -1;
  }

  so_count++;
  if(kernel_copyin(&so_count, file, sizeof(so_count))) {
    return -1;
  }
  return 0;
}


int
kernel_overlap_sockets(int pid, int master_sock, int victim_sock) {
  unsigned long master_inp6_outputopts;
  unsigned long victim_inp6_outputopts;
  unsigned long pktinfo;
  unsigned int tclass;

  if(kernel_inc_so_count(pid, master_sock)) {
    return -1;
  }

  if(!(master_inp6_outputopts=kernel_get_proc_inp6_outputopts(pid,
							      master_sock))) {
    return -1;
  }

  if(kernel_inc_so_count(pid, victim_sock)) {
    return -1;
  }

  if(!(victim_inp6_outputopts=kernel_get_proc_inp6_outputopts(pid,
							      victim_sock))) {
    return -1;
  }

  pktinfo = victim_inp6_outputopts + 0x10;
  if(kernel_copyin(&pktinfo, master_inp6_outputopts + 0x10,
		   sizeof(pktinfo))) {

    return -1;
  }

  tclass = 0x13370000;
  if(kernel_copyin(&tclass, master_inp6_outputopts + 0xc0, sizeof(tclass))) {
    return -1;
  }

  return 0;
}


unsigned long
kernel_get_proc_rootdir(int pid) {
  unsigned long filedesc = 0;
  unsigned long vnode = 0;

  if(!(filedesc=kernel_get_proc_filedesc(pid))) {
    return 0;
  }

  if(kernel_copyout(filedesc + KERNEL_OFFSET_FILEDESC_FD_RDIR, &vnode,
		    sizeof(vnode))) {
    return 0;
  }

  return vnode;
}


unsigned long
kernel_get_proc_jaildir(int pid) {
  unsigned long filedesc = 0;
  unsigned long vnode = 0;

  if(!(filedesc=kernel_get_proc_filedesc(pid))) {
    return 0;
  }

  if(kernel_copyout(filedesc + KERNEL_OFFSET_FILEDESC_FD_JDIR, &vnode,
		    sizeof(vnode))) {
    return 0;
  }

  return vnode;
}


int
kernel_set_proc_rootdir(int pid, unsigned long vnode) {
  unsigned long filedesc = 0;

  if(!(filedesc=kernel_get_proc_filedesc(pid))) {
    return 0;
  }

  if(kernel_copyin(&vnode, filedesc + KERNEL_OFFSET_FILEDESC_FD_RDIR,
		   sizeof(vnode))) {
    return -1;
  }

  return 0;
}


int
kernel_set_proc_jaildir(int pid, unsigned long vnode) {
  unsigned long filedesc = 0;

  if(!(filedesc=kernel_get_proc_filedesc(pid))) {
    return 0;
  }

  if(kernel_copyin(&vnode, filedesc + KERNEL_OFFSET_FILEDESC_FD_JDIR,
		   sizeof(vnode))) {
    return -1;
  }

  return 0;
}
