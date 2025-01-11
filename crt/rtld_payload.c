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
#include "rtld_payload.h"


/**
 * Standard posix macros.
 **/
#define ENOENT 2
#define ENOMEM 12
#define EINVAL 22
#define ENOSYS 78


/**
 * Extend rtld_lib_t anonymously with auxiliary parameters needed
 * for resolving symbols in the payload needed by shared objects.
 **/
typedef struct rtld_payload_lib {
  struct rtld_lib;

  Elf64_Sym* symtab;
  char* strtab;
  unsigned long symtab_size;
} rtld_payload_lib_t;


/**
 * Data structure used by dladdr().
 **/
typedef struct rtld_lib_seq {
  struct rtld_lib *lib;
  struct rtld_lib_seq *next;
} rtld_lib_seq_t;


/**
 * Dependencies to standard libraries.
 **/
static int (*strcmp)(const char*, const char*) = 0;
static void* (*memcpy)(void*, const void*, unsigned long) = 0;
static char* (*_Strerror)(int, char*) = 0;

static void* (*calloc)(unsigned long, unsigned long) = 0;
static void (*free)(void*) = 0;


/**
 * Dependencies provided by the ELF linker.
 **/
extern unsigned char __image_start[] __attribute__((weak));
extern unsigned char __image_end[] __attribute__((weak));
extern Elf64_Dyn _DYNAMIC[];


/**
 * Foward declaration needed to initialze g_this.
 **/
static int this_open(rtld_lib_t* ctx);
static void* this_sym2addr(rtld_lib_t* ctx, const char* name);
static const char* this_addr2sym(rtld_lib_t* ctx, void* addr);
static int this_close(rtld_lib_t* ctx);
static void this_destroy(rtld_lib_t* ctx);


/**
 * Handle to the root node in the lib dependency graph.
 **/
static rtld_payload_lib_t* g_this = 0;


/**
 * Define variables needed by dlerror() and dladdr().
 **/
static int g_dlerrno = 0;
static rtld_lib_seq_t* g_libseq = 0;


/**
 * Process the DT_NEEDED entry in the .dynamic section.
 **/
static int
dt_needed(const char* soname) {
  rtld_lib_t* it = (rtld_lib_t*)g_this;
  rtld_lib_t* lib = 0;

  while(it->next) {
    it = it->next;
  }

  if(!(lib=__rtld_lib_new(it, soname))) {
    klog_printf("Unable to load %s\n", soname);
    return -1;

  } else if(__rtld_lib_open(lib) < 0) {
    klog_printf("unable to load '%s'\n", soname);
    __rtld_lib_destroy(lib);
    return -1;
  }

  it->next = lib;

  return 0;
}


/**
 * Process the R_X86_64_GLOB_DAT relocation type.
 **/
static int
r_glob_dat(Elf64_Rela* rela) {
  unsigned long loc = (unsigned long)(__image_start + rela->r_offset);
  Elf64_Sym* sym = g_this->symtab + ELF64_R_SYM(rela->r_info);
  const char* name = g_this->strtab + sym->st_name;
  void* val = 0;

  for(rtld_lib_t *lib=g_this->next; lib; lib=lib->next) {
    if((val=__rtld_lib_sym2addr(lib, name))) {
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
  Elf64_Sym* sym = g_this->symtab + ELF64_R_SYM(rela->r_info);
  const char* name = g_this->strtab + sym->st_name;
  void* val = 0;

  // check if symbol is provided by a child
  for(rtld_lib_t *lib=g_this->next; lib!=0; lib=lib->next) {
    if((val=__rtld_lib_sym2addr(lib, name))) {
      val += rela->r_addend;
      return mdbg_copyin(-1, &val, loc, sizeof(val));
    }
  }

  // ignore unresolved weak symbols
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
 *  Figure out the symtab size.
 **/
static unsigned int
dynsym_count(unsigned int *gnu_hash) {
  unsigned int nbuckets = gnu_hash[0];
  unsigned int symoffset = gnu_hash[1];
  unsigned int bloom_size = gnu_hash[2];
  unsigned long *bloom = (unsigned long *)(gnu_hash + 4);
  unsigned int *buckets = (unsigned int *)(bloom + bloom_size);
  unsigned int *chain = buckets + nbuckets;
  unsigned int max_index = 0;
  unsigned int index = 0;

  for(unsigned int i=0; i<nbuckets; i++) {
    if(buckets[i] == 0) {
      continue;
    }

    index = buckets[i];
    while(1) {
      if(chain[index-symoffset] & 1) {
        break;
      }
      index++;
    }

    if(index > max_index) {
      max_index = index;
    }
  }

  return max_index + 1;
}


/**
 * Load payload data into memory.
 **/
static int
payload_load(void) {
  unsigned int *gnu_hash = 0;
  unsigned long relasz = 0;
  unsigned long pltsz = 0;
  Elf64_Rela* rela = 0;
  Elf64_Rela* plt = 0;

  // find lookup tables
  for(int i=0; _DYNAMIC[i].d_tag!=DT_NULL; i++) {
    switch(_DYNAMIC[i].d_tag) {
    case DT_SYMTAB:
      g_this->symtab = (Elf64_Sym*)(__image_start + _DYNAMIC[i].d_un.d_ptr);
      break;

    case DT_STRTAB:
      g_this->strtab = (char*)(__image_start + _DYNAMIC[i].d_un.d_ptr);
      break;

    case DT_GNU_HASH:
      gnu_hash = (unsigned int*)(__image_start + _DYNAMIC[i].d_un.d_ptr);
      break;

    case DT_RELA:
      rela = (Elf64_Rela*)(__image_start + _DYNAMIC[i].d_un.d_ptr);
      break;

    case DT_RELASZ:
      relasz = _DYNAMIC[i].d_un.d_val;
      break;

    case DT_JMPREL:
      plt = (Elf64_Rela*)(__image_start + _DYNAMIC[i].d_un.d_ptr);
      break;

    case DT_PLTRELSZ:
      pltsz = _DYNAMIC[i].d_un.d_val;
      break;
    }
  }

  // symtab size is determined using DT_GNU_HASH
  if(gnu_hash) {
    g_this->symtab_size = dynsym_count(gnu_hash) * sizeof(Elf64_Sym);
  }

  // load needed libraries
  for(int i=0; _DYNAMIC[i].d_tag!=DT_NULL; i++) {
    switch(_DYNAMIC[i].d_tag) {
    case DT_NEEDED:
      if(dt_needed(g_this->strtab + _DYNAMIC[i].d_un.d_val)) {
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

    default:
      klog_printf("Unsupported relocation type %x\n",
                  rela[i].r_info);
      return -1;
    }
  }

  for(int i=0; i<pltsz/sizeof(Elf64_Rela); i++) {
    switch(plt[i].r_info & 0xffffffffl) {
    case R_X86_64_JMP_SLOT:
      if(r_jmp_slot(&plt[i])) {
	return -1;
      }
      break;

    default:
      klog_printf("Unsupported plt type %x\n",
                  plt[i].r_info);
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

  if(!KERNEL_DLSYM(0x2, calloc)) {
    return -1;
  }
  if(!KERNEL_DLSYM(0x2, free)) {
    return -1;
  }
  if(!KERNEL_DLSYM(0x2, strcmp)) {
    return -1;
  }
  if(!KERNEL_DLSYM(0x2, memcpy)) {
    return -1;
  }
  if(!KERNEL_DLSYM(0x2, _Strerror)) {
      return -1;
  }

  g_this = calloc(1, sizeof(rtld_payload_lib_t));
  g_this->open     = this_open;
  g_this->sym2addr = this_sym2addr;
  g_this->addr2sym = this_addr2sym;
  g_this->close    = this_close;
  g_this->destroy  = this_destroy;
  g_this->refcnt   = 1;
  g_this->mapbase  = __image_start;
  g_this->mapsize  = __image_end - __image_start;

  __syscall(0x268, pid, g_this->soname, 1024);

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
  int err = 0;

  if(g_this) {
    if(g_this->next) {
      err = __rtld_lib_close(g_this->next);
    }
    free(g_this);
  }

  return err;
}


static int
this_open(rtld_lib_t* ctx) {
  return 0;
}


static void*
this_sym2addr(rtld_lib_t* ctx, const char* name) {
  if(ctx != (rtld_lib_t*)g_this) {
    return 0;
  }

  if(!g_this->symtab || !g_this->strtab) {
    return 0;
  }

  for(unsigned long i=0; i<g_this->symtab_size/sizeof(Elf64_Sym); i++) {
    if(!g_this->symtab[i].st_size) {
      continue;
    }

    if(!strcmp(name, g_this->strtab + g_this->symtab[i].st_name)) {
      return __image_start + g_this->symtab[i].st_value;
    }
  }

  return 0;
}


static const char*
this_addr2sym(rtld_lib_t* ctx, void* addr) {
  rtld_payload_lib_t* lib = (rtld_payload_lib_t*)ctx;

  if(lib != g_this) {
    return 0;
  }
  if(!lib->symtab || !lib->strtab) {
    return 0;
  }

  if(addr < lib->mapbase ||
     addr > lib->mapbase + lib->mapsize) {
    return 0;
  }

  for(unsigned long i=0; i<lib->symtab_size/sizeof(Elf64_Sym); i++) {
    if(!g_this->symtab[i].st_size) {
      continue;
    }

    if(addr >= lib->mapbase + lib->symtab[i].st_value &&
       addr <= lib->mapbase + lib->symtab[i].st_value + lib->symtab[i].st_size) {
      return lib->strtab + lib->symtab[i].st_name;
    }
  }

  return 0;
}


static int
this_close(rtld_lib_t* ctx) {
  return 0;
}


static void
this_destroy(rtld_lib_t* ctx) {
}


void*
__dlopen(const char *filename, int flags) {
  unsigned char privcaps[16] = {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
                                0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
  unsigned char caps[16];
  rtld_lib_seq_t *seq;
  rtld_lib_t* last;
  rtld_lib_t* lib;

  if(!(flags & RTLD_MODEMASK)) {
    g_dlerrno = EINVAL;
    return 0;
  }
  if(flags & RTLD_TRACE) {
    g_dlerrno = ENOSYS;
    return 0;
  }
  if(flags & RTLD_NOLOAD) {
    g_dlerrno = ENOSYS;
    return 0;
  }

  /*
  if(flags & RTLD_LAZY) {
    g_dlerrno = ENOSYS;
    return 0;
  }
  */

  if(!filename) {
      return g_this;
  }

  last = (rtld_lib_t*)g_this;
  while(last && last->next) {
      last = last->next;
  }

  if(!(lib=__rtld_lib_new(last, filename))) {
    g_dlerrno = ENOMEM;
    return 0;
  }

  if(kernel_get_ucred_caps(-1, caps)) {
    g_dlerrno = -1;
    return 0;
  }
  if(kernel_set_ucred_caps(-1, privcaps)) {
    g_dlerrno = -1;
    return 0;
  }

  if((g_dlerrno=__rtld_lib_open(lib))) {
    __rtld_lib_destroy(lib);
    kernel_set_ucred_caps(-1, caps);
    return 0;
  }

  if(kernel_set_ucred_caps(-1, caps)) {
    __rtld_lib_close(lib);
    g_dlerrno = -1;
    return 0;
  }

  if((flags & RTLD_LOCAL) || !(flags & RTLD_GLOBAL)) {
    last->next = 0;
  }

  seq = calloc(1, sizeof(rtld_lib_seq_t));
  seq->next = g_libseq;
  seq->lib  = lib;
  g_libseq  = seq;

  g_dlerrno = 0;

  return lib;
}


int
__dladdr(void *addr, Dl_info *info) {
  rtld_lib_t* lib;

  for(lib=(rtld_lib_t*)g_this; lib; lib=lib->next) {
    if(addr >= lib->mapbase &&
       addr < lib->mapbase + lib->mapsize) {
      info->dli_fname = lib->soname;
      info->dli_fbase = lib->mapbase;
      info->dli_sname = __rtld_lib_addr2sym(lib, addr);
      info->dli_saddr = __rtld_lib_sym2addr(lib, info->dli_sname);
      return 1;
    }
  }

  for(rtld_lib_seq_t* seq=g_libseq; seq; seq=seq->next) {
    if(addr >= seq->lib->mapbase &&
       addr < seq->lib->mapbase + seq->lib->mapsize) {
      info->dli_fname = seq->lib->soname;
      info->dli_fbase = seq->lib->mapbase;
      info->dli_sname = __rtld_lib_addr2sym(seq->lib, addr);
      info->dli_saddr = __rtld_lib_sym2addr(seq->lib, info->dli_sname);
      return 1;
    }
  }

  g_dlerrno = EINVAL;

  return 0;
}


void*
__dlsym(void *handle, const char *symbol) {
  rtld_lib_t* lib = handle;
  void* addr = 0;

  if(handle == 0) {
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
  if(handle == RTLD_DEFAULT) {
    lib = (rtld_lib_t*)g_this;
  }

  while(lib) {
    if((addr=__rtld_lib_sym2addr(lib, symbol))) {
      return addr;
    }
    lib = lib->next;
  }

  g_dlerrno = EINVAL;
  return 0;
}


int
__dlclose(void *handle) {
  rtld_lib_seq_t *prev = 0;
  rtld_lib_seq_t *seq = 0;

  if(g_this == handle) {
    g_dlerrno = -1;
    return g_dlerrno;
  }

  for(seq=g_libseq; seq; prev=seq, seq=seq->next) {
      if(seq->lib == handle) {
          break;
      }
  }

  if(!seq) {
      g_dlerrno = -1;
      return g_dlerrno;
  }

  if(prev) {
      prev->next = seq->next;
  } else {
      g_libseq = seq->next;
  }

  g_dlerrno = __rtld_lib_close(handle);

  return g_dlerrno;
}


char*
__dlerror(void) {
  if(g_dlerrno) {
    return _Strerror(g_dlerrno, 0);
  }

  return 0;
}
