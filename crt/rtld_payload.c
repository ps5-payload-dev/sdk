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
#include "klog.h"
#include "mdbg.h"
#include "syscall.h"
#include "rtld.h"


/**
 * Dependencies to standard libraries.
 **/
static void* (*memcpy)(void*, const void*, unsigned long) = 0;
static char* (*_Strerror)(int, char*) = 0;


/**
 * Dependencies provided by the ELF linker.
 **/
extern unsigned char __image_start[] __attribute__((weak));
extern Elf64_Dyn _DYNAMIC[];


/**
 * Global variables.
 **/
static rtld_lib_t* g_libhead = 0;
static Elf64_Sym* g_symtab = 0;
static char* g_strtab = 0;


/**
 * Process the DT_NEEDED entry in the .dynamic section.
 **/
static int
dt_needed(const char* soname) {
  rtld_lib_t* it = g_libhead;
  rtld_lib_t* lib;

  while(it && it->next) {
    it = it->next;
  }

  if(!(lib=__rtld_lib_new(it, soname))) {
    klog_printf("Unable to load %s\n", soname);
    return -1;

  } else if(__rtld_lib_open(lib) < 0) {
    klog_printf("unable to load '%s'\n", soname);
    __rtld_lib_destroy(lib);
    return -1;

  } else if(!g_libhead) {
    g_libhead = lib;

  } else if(it) {
    it->next = lib;
  }

  return 0;
}


/**
 * Process the R_X86_64_GLOB_DAT relocation type.
 **/
static int
r_glob_dat(Elf64_Rela* rela) {
  unsigned long loc = (unsigned long)(__image_start + rela->r_offset);
  Elf64_Sym* sym = g_symtab + ELF64_R_SYM(rela->r_info);
  const char* name = g_strtab + sym->st_name;
  void* val = 0;

  for(rtld_lib_t *lib=g_libhead; lib; lib=lib->next) {
    if((val=__rtld_lib_sym(lib, name))) {
      return mdbg_copyin(-1, &val, loc, sizeof(val));
    }
  }

  if(ELF64_ST_BIND(sym->st_info) == STB_WEAK) {
    return 0;
  }

  klog_printf("Unable to resolve '%s'\n", name);

  return -1;
}


/**
 * Process the R_X86_64_JMP_SLOT relocation type.
 **/
static int
r_jmp_slot(Elf64_Rela* rela) {
  return r_glob_dat(rela);
}


/**
 * Process the R_X86_64_64 relocation type.
 **/
static int
r_direct_64(Elf64_Rela* rela) {
  unsigned long loc = (unsigned long)(__image_start + rela->r_offset);
  Elf64_Sym* sym = g_symtab + ELF64_R_SYM(rela->r_info);
  const char* name = g_strtab + sym->st_name;
  void* val = 0;

  for(rtld_lib_t *lib=g_libhead; lib!=0; lib=lib->next) {
    if((val=__rtld_lib_sym(lib, name))) {
      val += rela->r_addend;
      return mdbg_copyin(-1, &val, loc, sizeof(val));
    }
  }

  if(ELF64_ST_BIND(sym->st_info) == STB_WEAK) {
    return 0;
  }

  klog_printf("Unable to resolve '%s'\n", name);

  return -1;
}


/**
 * Process the R_X86_64_RELATIVE relocation type.
 **/
static int
r_relative(Elf64_Rela* rela) {
  unsigned long loc = (unsigned long)(__image_start + rela->r_offset);
  unsigned long val = (unsigned long)(__image_start + rela->r_addend);

  // ELF loader allready applied relocation
  if(*((unsigned long*)loc) == val) {
      return 0;
  }

  if(mdbg_copyin(-1, &val, loc, sizeof(val))) {
    klog_perror("mdbg_copyin");
    return -1;
  }

  return 0;
}


/**
 *
 **/
static int
payload_load(void) {
  Elf64_Rela* rela = 0;
  long relasz = 0;

  // find lookup tables
  for(int i=0; _DYNAMIC[i].d_tag!=DT_NULL; i++) {
    switch(_DYNAMIC[i].d_tag) {
    case DT_SYMTAB:
      g_symtab = (Elf64_Sym*)(__image_start + _DYNAMIC[i].d_un.d_ptr);
      break;

    case DT_STRTAB:
      g_strtab = (char*)(__image_start + _DYNAMIC[i].d_un.d_ptr);
      break;

    case DT_RELA:
      rela = (Elf64_Rela*)(__image_start + _DYNAMIC[i].d_un.d_ptr);
      break;

    case DT_RELASZ:
      relasz = _DYNAMIC[i].d_un.d_val;
      break;
    }
  }

  // load needed libraries
  for(int i=0; _DYNAMIC[i].d_tag!=DT_NULL; i++) {
    switch(_DYNAMIC[i].d_tag) {
    case DT_NEEDED:
      if(dt_needed(g_strtab + _DYNAMIC[i].d_un.d_val)) {
	return -1;
      }
      break;
    }
  }

  // apply relocations
  for(int i=0; i<relasz/sizeof(Elf64_Rela); i++) {
    switch(rela[i].r_info & 0xffffffffl) {
    case R_X86_64_JMP_SLOT:
      if(r_jmp_slot(&rela[i])) {
	return -1;
      }
      break;

    case R_X86_64_64:
      if(r_direct_64(&rela[i])) {
	return -1;
      }
      break;

    case R_X86_64_GLOB_DAT:
      if(r_glob_dat(&rela[i])) {
	return -1;
      }
      break;

    case R_X86_64_RELATIVE:
      if(r_relative(&rela[i])) {
	return -1;
      }
      break;
    }
  }

  return 0;
}


int
__rtld_payload_init(void) {
  static const unsigned char privcaps[16] = {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
					     0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
  int pid = __syscall(SYS_getpid);
  unsigned char caps[16];
  unsigned long rootdir;
  int err;

  if(!(rootdir=kernel_get_proc_rootdir(pid))) {
    return -1;
  }
  if(kernel_get_ucred_caps(pid, caps)) {
    return -1;
  }
  if(kernel_set_proc_rootdir(pid, kernel_get_root_vnode())) {
    return -1;
  }
  if(kernel_set_ucred_caps(pid, privcaps)) {
    return -1;
  }

  if(!KERNEL_DLSYM(0x2, memcpy)) {
    return -1;
  }
  if(!KERNEL_DLSYM(0x2, _Strerror)) {
      return -1;
  }

  err = payload_load();

  if(kernel_set_proc_rootdir(pid, rootdir)) {
    return -1;
  }
  if(kernel_set_ucred_caps(pid, caps)) {
    return -1;
  }

  return err;
}


int
__rtld_payload_fini(void) {
  int err;

  err =__rtld_lib_close(g_libhead);
  __rtld_lib_destroy(g_libhead);

  return err;
}

#define RTLD_NEXT    ((void*)-1)
#define RTLD_DEFAULT ((void*)-2)
#define RTLD_SELF    ((void*)-3)

#define RTLD_LAZY     0x0001
#define RTLD_NOW      0x0002
#define RTLD_MODEMASK 0x0003
#define RTLD_GLOBAL   0x0100
#define RTLD_LOCAL    0x0000
#define RTLD_TRACE    0x0200
#define RTLD_NODELETE 0x1000
#define RTLD_NOLOAD   0x2000

#define ENOENT 2
#define ENOMEM 12
#define EINVAL 22
#define ENOSYS 78


static int g_dlerrno = 0;



void*
dlopen(const char *filename, int flags) {
  rtld_lib_t* lib;

  if(!(flags & RTLD_MODEMASK)) {
    g_dlerrno = EINVAL;
    return 0;
  }
  if(flags & RTLD_TRACE) {
    g_dlerrno = ENOSYS;
    return 0;
  }
  if(flags & RTLD_NOW) {
    g_dlerrno = ENOSYS;
    return 0;
  }
  if(flags & RTLD_GLOBAL) {
    g_dlerrno = ENOSYS;
    return 0;
  }

  if(!(lib=__rtld_lib_new(0, filename))) {
    g_dlerrno = ENOMEM;
    return 0;
  }
  if((g_dlerrno=__rtld_lib_open(lib))) {
    __rtld_lib_destroy(lib);
    return 0;
  }

  g_dlerrno = 0;
  return lib;
}


void*
dlsym(void *handle, const char *symbol) {
  void* addr;

  if(handle == 0) {
    g_dlerrno = ENOSYS;
    return 0;
  }
  if(handle == RTLD_DEFAULT) {
    g_dlerrno = ENOSYS;
    return 0;
  }
  if(handle == RTLD_NEXT) {
    g_dlerrno = ENOSYS;
    return 0;
  }
  if(handle == RTLD_SELF) {
    g_dlerrno = ENOSYS;
    return 0;
  }

  if(!(addr=__rtld_lib_sym(handle, symbol))) {
    g_dlerrno = EINVAL;
    return 0;
  }

  g_dlerrno = 0;
  return addr;
}


int
dlclose(void *handle) {
  if(!(g_dlerrno=__rtld_lib_close(handle))) {
    __rtld_lib_destroy(handle);
  }

  return g_dlerrno;
}


char*
dlerror(void) {
  if(g_dlerrno) {
    return _Strerror(g_dlerrno, 0);
  }

  return 0;
}
