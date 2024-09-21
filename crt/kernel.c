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

#include "klog.h"
#include "payload.h"
#include "syscall.h"

/**
 * standard macros.
 **/
#define IPPROTO_IPV6 41
#define IPV6_PKTINFO 46


/**
 * dynamic library loaded in kernel memory.
 **/
typedef struct dynlib_dynsec {
  struct {
    unsigned long le_next;
    unsigned long le_prev;
  } list_entry;

  unsigned long sysvec;
  unsigned int refcount;
  unsigned long size;

  unsigned long symtab;
  unsigned long symtabsize;

  unsigned long strtab;
  unsigned long strtabsize;

  unsigned long pltrela;
  unsigned long pltrelasize;

  unsigned long rela;
  unsigned long relasize;

  unsigned long hash;
  unsigned long hashsize;

  unsigned long dynamic;
  unsigned long dynamicsize;

  unsigned long sce_comment;
  unsigned long sce_commentsize;

  unsigned long sce_dynlib;
  unsigned long sce_dynlibsize;

  unsigned long unknown1;     // execpath?
  unsigned long unknown1size;

  unsigned long buckets;
  unsigned long bucketssize;
  unsigned int nbuckets;

  unsigned long chains;
  unsigned long chainssize;
  unsigned int nchains;

  unsigned long unknown2[7];
} dynlib_dynsec_t;


/**
 * an ELF loaded in kernel memory.
 **/
typedef struct dynlib_obj {
  unsigned long next;
  unsigned long path;
  unsigned long unknown0[2];
  unsigned int refcount;
  unsigned long handle;

  unsigned long mapbase;
  unsigned long mapsize;
  unsigned long textsize;

  unsigned long database;
  unsigned long datasize;

  unsigned long unknown1;
  unsigned long unknown1size;

  unsigned long entry;
  unsigned long unknown2;
  unsigned long vaddrbase;

  unsigned int tlsindex;
  unsigned long tlsinit;
  unsigned long tlsinitsize;
  unsigned long tlssize;
  unsigned long  tlsoffset;
  unsigned long tlsalign;

  unsigned long pltgot;

  unsigned long unknown3[6];

  unsigned long init;
  unsigned long fini;

  unsigned long eh_frame_hdr;
  unsigned long eh_frame_hdr_size;

  unsigned long eh_frame;
  unsigned long eh_frame_size;

  int status;
  int flags;

  unsigned long unknown4[5];
  unsigned long dynsec;
  unsigned long unknown5[6]; //fingerprint?
} dynlib_obj_t;


/**
 * an ELF symbol loaded in kernel memory.
 **/
typedef struct {
  unsigned int st_name;
  unsigned char st_info;
  unsigned char st_other;
  unsigned short st_shndx;
  unsigned long st_value;
  unsigned long st_size;
} Elf64_Sym;


/**
 * external dependencies.
 **/
static void* (*malloc)(unsigned long) = 0;
static void  (*free)(void*) = 0;
static int   (*strncmp)(const char*, const char*, unsigned long) = 0;
static int   (*strlen)(const char*) = 0;

/**
 * public constants.
 **/
unsigned long KERNEL_ADDRESS_DATA_BASE      = 0;
unsigned long KERNEL_ADDRESS_ALLPROC        = 0;
unsigned long KERNEL_ADDRESS_PRISON0        = 0;
unsigned long KERNEL_ADDRESS_ROOTVNODE      = 0;
unsigned long KERNEL_ADDRESS_SECURITY_FLAGS = 0;
unsigned long KERNEL_ADDRESS_UTOKEN_FLAGS   = 0;
unsigned long KERNEL_ADDRESS_QA_FLAGS       = 0;
unsigned long KERNEL_ADDRESS_TARGETID       = 0;

const unsigned long KERNEL_OFFSET_PROC_P_UCRED = 0x40;
const unsigned long KERNEL_OFFSET_PROC_P_FD    = 0x48;
const unsigned long KERNEL_OFFSET_PROC_P_PID   = 0xBC;

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


unsigned int
kernel_get_fw_version(void) {
  int mib[2] = {1, 46};
  unsigned long size = sizeof(mib);
  unsigned int version = 0;

  if(syscall(SYS_sysctl, mib, 2, &version, &size, 0, 0)) {
    return 0;
  }

  return version;
}


int
__kernel_init(payload_args_t* args) {
  int error = 0;

  if((error=args->sceKernelDlsym(0x2, "malloc", &malloc))) {
    klog_perror("Unable to resolve 'malloc'");
    return error;
  }
  if((error=args->sceKernelDlsym(0x2, "free", &free))) {
    klog_perror("Unable to resolve 'free'");
    return error;
  }
  if((error=args->sceKernelDlsym(0x2, "strlen", &strlen))) {
    klog_perror("Unable to resolve 'strlen'");
    return error;
  }
  if((error=args->sceKernelDlsym(0x2, "strncmp", &strncmp))) {
    klog_perror("Unable to resolve 'strncmp'");
    return error;
  }

  if((rw_pair[0]=args->rwpair[0]) < 0) {
    klog_puts("Invalid master socket");
    return -1;
  }
  if((rw_pair[1]=args->rwpair[1]) < 0) {
    klog_puts("Invalid victim socket");
    return -1;
  }

  if((rw_pipe[0]=args->rwpipe[0]) < 0) {
    klog_puts("Invalid kernel read handle");
    return -1;
  }
  if((rw_pipe[1]=args->rwpipe[1]) < 0) {
    klog_puts("Invalid kernel write handle");
    return -1;
  }

  if(!(pipe_addr=args->kpipe_addr)) {
    klog_puts("Invalid kernel pipe address");
    return -1;
  }
  if(!(KERNEL_ADDRESS_DATA_BASE=args->kdata_base_addr)) {
    klog_puts("Invalid kernel .data address");
    return -1;
  }

  switch(kernel_get_fw_version() & 0xffff0000) {
  case 0x2000000:
    KERNEL_ADDRESS_ALLPROC        = KERNEL_ADDRESS_DATA_BASE + 0x2701C28;
    KERNEL_ADDRESS_SECURITY_FLAGS = KERNEL_ADDRESS_DATA_BASE + 0x63E1274;
    KERNEL_ADDRESS_TARGETID       = KERNEL_ADDRESS_DATA_BASE + 0x63E127D;
    KERNEL_ADDRESS_QA_FLAGS       = KERNEL_ADDRESS_DATA_BASE + 0x63E1298;
    KERNEL_ADDRESS_UTOKEN_FLAGS   = KERNEL_ADDRESS_DATA_BASE + 0x63E1300;
    KERNEL_ADDRESS_PRISON0        = KERNEL_ADDRESS_DATA_BASE + 0x194BA60;
    KERNEL_ADDRESS_ROOTVNODE      = KERNEL_ADDRESS_DATA_BASE + 0x67134C0;
    break;
  case 0x2200000:
  case 0x2250000:
  case 0x2260000:
  case 0x2300000:
  case 0x2500000:
    KERNEL_ADDRESS_ALLPROC        = KERNEL_ADDRESS_DATA_BASE + 0x2701C28;
    KERNEL_ADDRESS_SECURITY_FLAGS = KERNEL_ADDRESS_DATA_BASE + 0x63E1274;
    KERNEL_ADDRESS_TARGETID       = KERNEL_ADDRESS_DATA_BASE + 0x63E127D;
    KERNEL_ADDRESS_QA_FLAGS       = KERNEL_ADDRESS_DATA_BASE + 0x63E1298;
    KERNEL_ADDRESS_UTOKEN_FLAGS   = KERNEL_ADDRESS_DATA_BASE + 0x63E1300;
    KERNEL_ADDRESS_PRISON0        = KERNEL_ADDRESS_DATA_BASE + 0x194BD20;
    KERNEL_ADDRESS_ROOTVNODE      = KERNEL_ADDRESS_DATA_BASE + 0x67134C0;
    break;
  case 0x3000000:
  case 0x3100000:
  case 0x3200000:
  case 0x3210000:
    KERNEL_ADDRESS_ALLPROC        = KERNEL_ADDRESS_DATA_BASE + 0x276DC58;
    KERNEL_ADDRESS_SECURITY_FLAGS = KERNEL_ADDRESS_DATA_BASE + 0x6466474;
    KERNEL_ADDRESS_TARGETID       = KERNEL_ADDRESS_DATA_BASE + 0x646647D;
    KERNEL_ADDRESS_QA_FLAGS       = KERNEL_ADDRESS_DATA_BASE + 0x6466498;
    KERNEL_ADDRESS_UTOKEN_FLAGS   = KERNEL_ADDRESS_DATA_BASE + 0x6466500;
    KERNEL_ADDRESS_PRISON0        = KERNEL_ADDRESS_DATA_BASE + 0x1CC2670;
    KERNEL_ADDRESS_ROOTVNODE      = KERNEL_ADDRESS_DATA_BASE + 0x67AB4C0;
    break;

  case 0x4020000:
    KERNEL_ADDRESS_ALLPROC        = KERNEL_ADDRESS_DATA_BASE + 0x27EDCB8;
    KERNEL_ADDRESS_SECURITY_FLAGS = KERNEL_ADDRESS_DATA_BASE + 0x6505474;
    KERNEL_ADDRESS_TARGETID       = KERNEL_ADDRESS_DATA_BASE + 0x650547D;
    KERNEL_ADDRESS_QA_FLAGS       = KERNEL_ADDRESS_DATA_BASE + 0x6505498;
    KERNEL_ADDRESS_UTOKEN_FLAGS   = KERNEL_ADDRESS_DATA_BASE + 0x6505500;
    KERNEL_ADDRESS_PRISON0        = KERNEL_ADDRESS_DATA_BASE + 0x1D34D00;
    KERNEL_ADDRESS_ROOTVNODE      = KERNEL_ADDRESS_DATA_BASE + 0x66E64C0;
    break;

  case 0x4000000:
  case 0x4030000:
  case 0x4500000:
  case 0x4510000:
    KERNEL_ADDRESS_ALLPROC        = KERNEL_ADDRESS_DATA_BASE + 0x27EDCB8;
    KERNEL_ADDRESS_SECURITY_FLAGS = KERNEL_ADDRESS_DATA_BASE + 0x6506474;
    KERNEL_ADDRESS_TARGETID       = KERNEL_ADDRESS_DATA_BASE + 0x650647D;
    KERNEL_ADDRESS_QA_FLAGS       = KERNEL_ADDRESS_DATA_BASE + 0x6506498;
    KERNEL_ADDRESS_UTOKEN_FLAGS   = KERNEL_ADDRESS_DATA_BASE + 0x6506500;
    KERNEL_ADDRESS_PRISON0        = KERNEL_ADDRESS_DATA_BASE + 0x1D34D00;
    KERNEL_ADDRESS_ROOTVNODE      = KERNEL_ADDRESS_DATA_BASE + 0x66E74C0;
    break;

  default:
    klog_printf("Unknown firmware 0x%x\n", kernel_get_fw_version());
    return -1;
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

  if(syscall(SYS_setsockopt, MASTER_SOCK, IPPROTO_IPV6, IPV6_PKTINFO,
	     victim_buf, 0x14)) {
    return -1;
  }

  if(syscall(SYS_setsockopt, VICTIM_SOCK, IPPROTO_IPV6, IPV6_PKTINFO,
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
  if(syscall(SYS_write, rw_pipe[1], uaddr, len) < 0) {
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
  if(syscall(SYS_read, rw_pipe[0], uaddr, len) < 0) {
    return -1;
  }

  return 0;
}


int
kernel_get_qaflags(unsigned char qaflags[16]) {
  return kernel_copyout(KERNEL_ADDRESS_QA_FLAGS, qaflags, 16);
}


int
kernel_set_qaflags(const unsigned char qaflags[16]) {
  return kernel_copyin(qaflags, KERNEL_ADDRESS_QA_FLAGS, 16);
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


static int
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
  dynlib_dynsec_t dynsec;
  unsigned long vaddr;
  Elf64_Sym *symtab;
  dynlib_obj_t obj;
  char *strtab;

  if(kernel_dynlib_obj(pid, handle, &obj)) {
    return 0;
  }

  if(kernel_copyout(obj.dynsec, &dynsec, sizeof(dynsec)) < 0) {
    return 0;
  }

  if(!(symtab=malloc(dynsec.symtabsize))) {
    return 0;
  }

  if(kernel_copyout(dynsec.symtab, symtab, dynsec.symtabsize) < 0) {
    free(symtab);
    return 0;
  }

  if(!(strtab=malloc(dynsec.strtabsize))) {
    free(symtab);
    return 0;
  }

  if(kernel_copyout(dynsec.strtab, strtab, dynsec.strtabsize) < 0) {
    free(symtab);
    free(strtab);
    return 0;
  }

  vaddr = 0;
  for(unsigned long i=0; i<dynsec.symtabsize / sizeof(Elf64_Sym); i++) {
    if(!strncmp(nid, strtab + symtab[i].st_name, 11)) {
      vaddr = obj.mapbase + symtab[i].st_value;
      break;
    }
  }

  free(symtab);
  free(strtab);

  return vaddr;
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
