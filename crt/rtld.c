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
#include "nid.h"
#include "syscall.h"


#define ELF64_R_SYM(info) ((info) >> 32)
#define ELF64_ST_BIND(info) ((info) >> 4)

#define STB_WEAK 2

#define DT_NULL    0
#define DT_NEEDED  1
#define DT_STRTAB  5
#define DT_SYMTAB  6
#define DT_RELA    7
#define DT_RELASZ  8

#define R_X86_64_64       1
#define R_X86_64_GLOB_DAT 6
#define R_X86_64_JMP_SLOT 7
#define R_X86_64_RELATIVE 8

#define RTLD_LAZY     0x0001
#define RTLD_NOW      0x0002
#define RTLD_MODEMASK 0x0003
#define RTLD_GLOBAL   0x0100
#define RTLD_LOCAL    0x0000
#define RTLD_TRACE    0x0200
#define RTLD_NODELETE 0x1000
#define RTLD_NOLOAD   0x2000

#define ENOENT 2
#define EINVAL 22
#define ENOSYS 78

#define DLSYM(handle, sym) (sym=(void*)kernel_dynlib_dlsym(-1, handle, #sym))


typedef struct {
  long d_tag;
  union {
    unsigned long d_val;
    unsigned long d_ptr;
  } d_un;
} Elf64_Dyn;


typedef struct {
  unsigned int   st_name;
  unsigned char  st_info;
  unsigned char  st_other;
  unsigned short st_shndx;
  unsigned long  st_value;
  unsigned long  st_size;
} Elf64_Sym;


typedef struct {
  unsigned long r_offset;
  unsigned long r_info;
  long          r_addend;
} Elf64_Rela;


typedef struct rtld_lib {
  int              handle;
  int              flags;
  unsigned long    mapbase;
  char            *strtab;
  Elf64_Sym       *symtab;
  unsigned long    symtabsize;
  struct rtld_lib* next;
} rtld_lib_t;


typedef struct sysmodtab {
  const char* name;
  unsigned int handle;
} sysmodtab_t;


/**
 * dependencies provided by the ELF linker.
 **/
extern unsigned char __image_start[] __attribute__((weak));
extern Elf64_Dyn _DYNAMIC[] __attribute__((weak));


/**
 * global private variables.
 **/
static rtld_lib_t* libhead = 0;
static Elf64_Sym* symtab = 0;
static char* strtab = 0;
static int libkernel_handle = 0;
static int dlerrno = 0;


/**
 * external dependencies.
 **/
static void* (*malloc)(unsigned long) = 0;
static void  (*free)(void*) = 0;
static char* (*strcat)(char*, const char*) = 0;
static char* (*strcpy)(char*, const char*) = 0;
static int   (*strcmp)(const char*, const char*) = 0;
static int   (*strncmp)(const char*, const char*, unsigned long) = 0;
static int   (*strlen)(const char*) = 0;
static int   (*sprintf)(char*, const char*, ...) = 0;
static char* (*getcwd)(char*, unsigned long) = 0;
static char* (*_Strerror)(int, char*) = 0;
static int   (*sceKernelLoadStartModule)(const char*, unsigned long, const void*,
					 unsigned int, void*, int*) = 0;
static int   (*sceKernelStopUnloadModule)(int, unsigned long, const void*, unsigned int,
					  const void*, void*) = 0;
static int   (*sceSysmoduleLoadModuleInternal)(unsigned int) = 0;


/**
 * lookup table for sceSysmoduleLoadModuleInternal().
 **/
static const sysmodtab_t sysmodtab[] = {
  {"libSceAbstractLocal.sprx", 0x8000005f},
  {"libSceAbstractStorage.sprx", 0x80000058},
  {"libSceAbstractTcs.sprx", 0x800000a1},
  {"libSceAbstractTwitter.sprx", 0x80000062},
  {"libSceAbstractYoutube.sprx", 0x80000061},
  {"libSceAc3Enc.sprx", 0x80000013},
  {"libSceAgc.sprx", 0x80000094},
  {"libSceAgcDriver.sprx", 0x80000080},
  {"libSceAgcResourceRegistration.sprx", 0x80000093},
  {"libSceAgcVsh.sprx", 0x80000086},
  {"libSceAgcVshDebug.sprx", 0x80000087},
  {"libSceAjm.native.sprx", 0x80000023},
  {"libSceAjmi.sprx", 0x8000007e},
  {"libSceAmpr.sprx", 0x800000b7},
  {"libSceAppChecker.sprx", 0x80000032},
  {"libSceAppDbShellCoreClient.sprx", 0x800000a7},
  {"libSceAppInstUtil.sprx", 0x80000014},
  {"libSceAsyncStorageInternal.sprx", 0x80000077},
  {"libSceAudioIn.sprx", 0x80000002},
  {"libSceAudioOut.sprx", 0x80000001},
  {"libSceAudioSystem.sprx", 0x80000083},
  {"libSceAudiodecCpuDtsHdMa.sprx", 0x8000002d},
  {"libSceAudiodecCpuLpcm.sprx", 0x8000002e},
  {"libSceAudiodecCpuTrhd.sprx", 0x80000082},
  {"libSceAvSetting.sprx", 0x80000021},
  {"libSceAvcap2.sprx", 0x80000085},
  {"libSceBackupRestoreUtil.sprx", 0x8000003f},
  {"libSceBgft.sprx", 0x8000002a},
  {"libSceBgsStorage.sprx", 0x800000a3},
  {"libSceCamera.sprx", 0x8000001a},
  {"libSceCdlgUtilServer.sprx", 0x80000007},
  {"libSceCommonDialog.sprx", 0x80000018},
  {"libSceComposite.sprx", 0x8000008a},
  {"libSceCompositeExt.sprx", 0x8000008b},
  {"libSceContentListController.sprx", 0x800000ad},
  {"libSceDataTransfer.sprx", 0x80000057},
  {"libSceDbg.sprx", 0x80000025},
  {"libSceDipsw.sprx", 0x80000029},
  {"libSceDseehx.sprx", 0x80000056},
  {"libSceDtsEnc.sprx", 0x80000028},
  {"libSceEmbeddedTts.sprx", 0x8000009c},
  {"libSceEmbeddedTtsCoreG3.sprx", 0x8000009b},
  {"libSceFsInternalForVsh.sprx", 0x80000066},
  {"libSceGLSlimVSH.sprx", 0x800000a9},
  {"libSceGifParser.sprx", 0x8000005e},
  {"libSceGpuCapture.sprx", 0x8000007f},
  {"libSceGpuTrace.sprx", 0x8000007b},
  {"libSceGvMp4Parser.sprx", 0x8000005c},
  {"libSceHidControl.sprx", 0x80000017},
  {"libSceHttp.sprx", 0x8000000a},
  {"libSceHttp2.sprx", 0x8000008c},
  {"libSceHttpCache.sprx", 0x80000078},
  {"libSceIcu.sprx", 0x800000a8},
  {"libSceIdu.sprx", 0x800000a6},
  {"libSceImageUtil.sprx", 0x80000059},
  {"libSceIpmi.sprx", 0x8000001d},
  {"libSceJemspace.sprx", 0x8000009e},
  {"libSceJitBridge.sprx", 0x8000006f},
  {"libSceJpegParser.sprx", 0x8000005b},
  {"libSceJsc.sprx", 0x800000b0},
  {"libSceJscCompiler.sprx", 0x80000070},
  {"libSceJxr.sprx", 0x800000b4},
  {"libSceJxrParser.sprx", 0x800000b5},
  {"libSceKbEmulate.sprx", 0x80000031},
  {"libSceLibreSsl.sprx", 0x80000065},
  {"libSceLibreSsl3.sprx", 0x800000b8},
  {"libSceLoginMgrServer.sprx", 0x80000045},
  {"libSceMarlin.sprx", 0x80000027},
  {"libSceMat.sprx", 0x80000048},
  {"libSceMbus.sprx", 0x8000001e},
  {"libSceMediaFrameworkInterface.sprx", 0x80000095},
  {"libSceMediaFrameworkUtil.sprx", 0x800000b6},
  {"libSceMetadataReaderWriter.sprx", 0x8000005a},
  {"libSceNKWeb.sprx", 0x80000079},
  {"libSceNKWebKit.sprx", 0x8000007a},
  {"libSceNet.sprx", 0x8000001c},
  {"libSceNetCtl.sprx", 0x80000009},
  {"libSceNgs2.sprx", 0x80000090},
  {"libSceNpCommon.sprx", 0x8000000c},
  {"libSceNpGameIntent.sprx", 0x8000008d},
  {"libSceNpManager.sprx", 0x8000000d},
  {"libSceNpRemotePlaySessionSignaling.sprx", 0x8000009a},
  {"libSceNpSns.sprx", 0x8000001b},
  {"libSceNpTcs.sprx", 0x800000a0},
  {"libSceNpWebApi.sprx", 0x8000000e},
  {"libSceNpWebApi2.sprx", 0x8000008f},
  {"libSceOpusCeltDec.sprx", 0x80000044},
  {"libSceOpusCeltEnc.sprx", 0x80000043},
  {"libSceOpusDec.sprx", 0x80000069},
  {"libSceOpusSilkEnc.sprx", 0x80000068},
  {"libSceOrbisCompat.sprx", 0x80000071},
  {"libScePad.sprx", 0x80000024},
  {"libScePngParser.sprx", 0x8000005d},
  {"libScePosixForWebKit.sprx", 0x80000098},
  {"libScePsm.sprx", 0x80000030},
  {"libSceRazorCpu_debug.sprx", 0x80000075},
  {"libSceRegMgr.sprx", 0x8000001f},
  {"libSceRemotePlayClientIpc.sprx", 0x800000b9},
  {"libSceResourceArbitrator.sprx", 0x80000092},
  {"libSceRnpsAppMgr.sprx", 0x80000076},
  {"libSceRtc.sprx", 0x80000020},
  {"libSceSaveData.sprx", 0x8000000f},
  {"libSceShareInternal.native.sprx", 0x8000008e},
  {"libSceSocialScreen.sprx", 0x800000ae},
  {"libSceSsl.sprx", 0x8000000b},
  {"libSceSulphaDrv.sprx", 0x8000003b},
  {"libSceSysCore.sprx", 0x80000004},
  {"libSceSysUtil.sprx", 0x80000026},
  {"libSceSystemLogger2.sprx", 0x800000b3},
  {"libSceSystemLogger2Delivery.sprx", 0x80000089},
  {"libSceSystemLogger2Game.sprx", 0x8000009f},
  {"libSceSystemLogger2NativeQueueClient.sprx", 0x80000088},
  {"libSceSystemService.sprx", 0x80000010},
  {"libSceSystemTts.sprx", 0x80000097},
  {"libSceTEEClient.sprx", 0x800000a2},
  {"libSceUserService.sprx", 0x80000011},
  {"libSceVcodec.sprx", 0x80000091},
  {"libSceVdecCore.native.sprx", 0x80000015},
  {"libSceVdecSavc2.native.sprx", 0x80000036},
  {"libSceVdecShevc.native.sprx", 0x8000003c},
  {"libSceVdecSvp9.native.sprx", 0x800000af},
  {"libSceVenc.sprx", 0x80000084},
  {"libSceVideoOut.sprx", 0x80000022},
  {"libSceVideoOutSecondary.sprx", 0x80000046},
  {"libSceVideoStreamingEngine_sys.sprx", 0x800000b2},
  {"libSceVisionManager.sprx", 0x80000012},
  {"libSceVnaInternal.sprx", 0x8000007c},
  {"libSceVnaWebsocket.sprx", 0x8000007d},
  {"libSceVoiceCommand.sprx", 0x80000099},
  {"libSceWeb.sprx", 0x80000072},
  {"libSceWebKit2.sprx", 0x80000073},
  {"libSceWebKit2Secure.sprx", 0x80000074},
  {"libSceWebmParserMdrw.sprx", 0x800000a4},
  {"libcairo.sprx", 0x800000ac},
  {"libcurl.sprx", 0x800000b1},
  {"libicu.sprx", 0x800000aa},
  {"libpng16.sprx", 0x800000ab}
};


/**
 * Log a symbol resolution error to /dev/klog
 **/
static void
klog_resolve_error(const char *name) {
  klog_printf("Unable to resolve the symbol '%s'\n", name);
}


/**
 * Log a library loading error to /dev/klog
 **/
static void
klog_libload_error(const char *name) {
  klog_printf("Unable to load the library '%s'\n", name);
}


/**
 * Get a pointer the the basename of a path
 **/
static const char*
rtld_basename(const char *path) {
  const char* ptr = path;

  while(path && *path) {
    if(*path == '/') {
      ptr = path+1;
    }
    path++;
  }

  return ptr;
}


/**
 * Figure out the absolute path to an sprx file.
 **/
static int
rtld_find_sprx(const char* cwd, const char* filename, char *path) {
  if(*filename == '/') {
    sprintf(path, "%s", filename);
  } else if(cwd) {
    sprintf(path, "%s/%s", cwd, filename);
  } else {
    sprintf(path, "%s", filename);
  }
  if(!__syscall(SYS_access, path, 0)) {
    return 0;
  }

  sprintf(path, "/system/priv/lib/%s", filename);
  if(!__syscall(SYS_access, path, 0)) {
      return 0;
  }

  sprintf(path, "/system/common/lib/%s", filename);
  if(!__syscall(SYS_access, path, 0)) {
      return 0;
  }

  sprintf(path, "/system_ex/priv_ex/lib/%s", filename);
  if(!__syscall(SYS_access, path, 0)) {
      return 0;
  }

  sprintf(path, "/system_ex/common_ex/lib/%s", filename);
  if(!__syscall(SYS_access, path, 0)) {
      return 0;
  }

  return -1;
}


/**
 *
 **/
static rtld_lib_t*
rtld_lib_new(int handle, int flags) {
  rtld_lib_t *lib = malloc(sizeof(rtld_lib_t));
  dynlib_dynsec_t dynsec;
  dynlib_obj_t obj;

  lib->handle = handle;
  lib->flags = flags;
  lib->mapbase = 0;
  lib->symtab = 0;
  lib->symtabsize = 0;
  lib->strtab = 0;
  lib->next = 0;

  if(kernel_dynlib_obj(-1, handle, &obj)) {
    return lib;
  }
  if(kernel_copyout(obj.dynsec, &dynsec, sizeof(dynsec)) < 0) {
    return lib;
  }
  if(!(lib->strtab=malloc(dynsec.strtabsize))) {
    return lib;
  }
  if(kernel_copyout(dynsec.strtab, lib->strtab, dynsec.strtabsize) < 0) {
    return lib;
  }
  if(!(lib->symtab=malloc(dynsec.symtabsize))) {
    return lib;
  }
  if(kernel_copyout(dynsec.symtab, lib->symtab, dynsec.symtabsize) < 0) {
    return lib;
  }

  lib->mapbase = obj.mapbase;
  lib->symtabsize = dynsec.symtabsize;

  return lib;
}


/**
 *
 **/
static rtld_lib_t*
rtld_open(const char* cwd, const char* filename, int flags) {
  const char *basename = rtld_basename(filename);
  int pid = __syscall(SYS_getpid);
  unsigned int handle;
  char path[0x4000];
  int error;

  if(!filename) {
    return rtld_lib_new(0, flags | RTLD_NODELETE);
  }

  if(!strcmp(basename, "libkernel.sprx") ||
     !strcmp(basename, "libkernel_web.sprx") ||
     !strcmp(basename, "libkernel_sys.sprx") ||
     !strcmp(basename, "libdl.sprx") ||
     !strcmp(basename, "libpthread.sprx")) {
    return rtld_lib_new(libkernel_handle, flags | RTLD_NODELETE);
  }

  if(!strcmp(basename, "libSceLibcInternal.sprx") ||
     !strcmp(basename, "libm.sprx")) {
    return rtld_lib_new(2, flags | RTLD_NODELETE);
  }

  if(!kernel_dynlib_handle(pid, basename, &handle)) {
    return rtld_lib_new(handle, flags | RTLD_NODELETE);
  }

  if(flags & RTLD_NOLOAD) {
    return 0;
  }

  if(rtld_find_sprx(cwd, filename, path)) {
    dlerrno = ENOENT;
    return 0;
  }

  for(int i=0; i<sizeof(sysmodtab)/sizeof(sysmodtab[0]); i++) {
    if(!strcmp(basename, sysmodtab[i].name)) {
      if((error=sceSysmoduleLoadModuleInternal(sysmodtab[i].handle))) {
	dlerrno = error;
	return 0;
      }
    }
  }

  if((handle=sceKernelLoadStartModule(path, 0, 0, 0, 0, 0)) < 0) {
    dlerrno = handle;
    return 0;
  }

  return rtld_lib_new(handle, flags);
}


/**
 *
 **/
static unsigned long
rtld_sym(rtld_lib_t* lib, const char* name) {
  unsigned long addr = 0;
  char nid[12];

  nid_encode(name, nid);

  for(unsigned long i=0; i<lib->symtabsize/sizeof(Elf64_Sym); i++) {
    if(!lib->symtab[i].st_value) {
      continue;
    }

    if(!strncmp(nid, lib->strtab + lib->symtab[i].st_name, 11)) {
      addr = lib->mapbase + lib->symtab[i].st_value;
      break;
    }
  }

  return addr;
}


/**
 *
 **/
static int
rtld_close(rtld_lib_t* lib) {
  int handle = lib->handle;
  int flags = lib->flags;
  int error = 0;

  if(lib->symtab) {
    free(lib->symtab);
  }
  if(lib->strtab) {
    free(lib->strtab);
  }

  free(lib);

  if(!(flags & RTLD_NODELETE)) {
    if((error=sceKernelStopUnloadModule(handle, 0, 0, 0, 0, 0))) {
      dlerrno = error;
    }
  }

  return error;
}


/**
 *
 **/
static int
dt_needed(const char* filename) {
  char sprx[0x1000];
  rtld_lib_t* lib;

  if((lib=rtld_open(0, filename, RTLD_LAZY))) {
    lib->next = libhead;
    libhead = lib;
    return 0;
  }

  klog_libload_error(sprx);

  return -1;
}


/**
 *
 **/
static int
r_glob_dat(Elf64_Rela* rela) {
  unsigned long loc = (unsigned long)(__image_start + rela->r_offset);
  Elf64_Sym* sym = symtab + ELF64_R_SYM(rela->r_info);
  const char* name = strtab + sym->st_name;
  unsigned long val = 0;

  for(rtld_lib_t *lib=libhead; lib!=0; lib=lib->next) {
    if((val=rtld_sym(lib, name))) {
      return mdbg_copyin(-1, &val, loc, sizeof(val));
    }
  }

  if(ELF64_ST_BIND(sym->st_info) == STB_WEAK) {
    return 0;
  }

  klog_resolve_error(name);

  return -1;
}


/**
 *
 **/
static int
r_jmp_slot(Elf64_Rela* rela) {
  return r_glob_dat(rela);
}


/**
 *
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
r_direct_64(Elf64_Rela* rela) {
  unsigned long loc = (unsigned long)(__image_start + rela->r_offset);
  Elf64_Sym* sym = symtab + ELF64_R_SYM(rela->r_info);
  const char* name = strtab + sym->st_name;
  unsigned long val = 0;

  for(rtld_lib_t *lib=libhead; lib!=0; lib=lib->next) {
    if((val=rtld_sym(lib, name))) {
      val += rela->r_addend;
      return mdbg_copyin(-1, &val, loc, sizeof(val));
    }
  }

  if(ELF64_ST_BIND(sym->st_info) == STB_WEAK) {
    return 0;
  }

  klog_resolve_error(name);

  return -1;
}


/**
 *
 **/
static int
rtld_load(void) {
  Elf64_Rela* rela = 0;
  long relasz = 0;

  // find lookup tables
  for(int i=0; _DYNAMIC[i].d_tag!=DT_NULL; i++) {
    switch(_DYNAMIC[i].d_tag) {
    case DT_SYMTAB:
      symtab = (Elf64_Sym*)(__image_start + _DYNAMIC[i].d_un.d_ptr);
      break;

    case DT_STRTAB:
      strtab = (char*)(__image_start + _DYNAMIC[i].d_un.d_ptr);
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
      if(dt_needed(strtab + _DYNAMIC[i].d_un.d_val)) {
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


/**
 *
 **/
static int
rtld_load_sysmodule(void) {
  int pid = __syscall(SYS_getpid);
  unsigned int handle;

  if(kernel_dynlib_handle(pid, "libSceSysmodule.sprx", &handle)) {
    if((handle=sceKernelLoadStartModule("/system/common/lib/libSceSysmodule.sprx",
					0, 0, 0, 0, 0)) <= 0) {
      klog_libload_error("libSceSysmodule.sprx");
      return -1;
    }
  }

  if(!DLSYM(handle, sceSysmoduleLoadModuleInternal)) {
    klog_resolve_error("sceSysmoduleLoadModuleInternal");
    return -1;
  }

  return 0;
}


int
__rtld_init(void) {
  static const unsigned char privcaps[16] = {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
					     0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
  int pid = __syscall(SYS_getpid);
  unsigned long rootdir = 0;
  unsigned char caps[16];
  int error = 0;

  // determine libkernel handle
  if(kernel_dynlib_dlsym(pid, 0x1, "sceKernelDlsym")) {
    libkernel_handle = 0x1;
  } else if(kernel_dynlib_dlsym(pid, 0x2001, "sceKernelDlsym")) {
    libkernel_handle = 0x2001;
  } else {
    klog_puts("Unable to determine libkernel handle");
    return -1;
  }

  // load deps to libc
  if(!DLSYM(0x2, malloc)) {
    klog_resolve_error("malloc");
    return -1;
  }
  if(!DLSYM(0x2, free)) {
    klog_resolve_error("free");
    return -1;
  }
  if(!DLSYM(0x2, strcat)) {
    klog_resolve_error("strcat");
    return -1;
  }
  if(!DLSYM(0x2, strcpy)) {
    klog_resolve_error("strcpy");
    return -1;
  }
  if(!DLSYM(0x2, strcmp)) {
    klog_resolve_error("strcmp");
    return -1;
  }
  if(!DLSYM(0x2, strncmp)) {
    klog_resolve_error("strncmp");
    return -1;
  }
  if(!DLSYM(0x2, strlen)) {
    klog_resolve_error("strlen");
    return -1;
  }
  if(!DLSYM(0x2, sprintf)) {
    klog_resolve_error("sprintf");
    return -1;
  }
  if(!DLSYM(0x2, getcwd)) {
    klog_resolve_error("getcwd");
    return -1;
  }
  if(!DLSYM(0x2, _Strerror)) {
    klog_resolve_error("_Strerror");
    return -1;
  }

  // load deps to libkernel
  if(!DLSYM(libkernel_handle, sceKernelLoadStartModule)) {
    klog_resolve_error("sceKernelLoadStartModule");
    return -1;
  }
  if(!DLSYM(libkernel_handle, sceKernelStopUnloadModule)) {
    klog_resolve_error("sceKernelStopUnloadModule");
    return -1;
  }

  // jailbreak, raise caps
  if(!(rootdir=kernel_get_proc_rootdir(pid))) {
    klog_puts("kernel_get_proc_rootdir failed");
    return -1;
  }
  if(kernel_get_ucred_caps(pid, caps)) {
    klog_puts("kernel_get_ucred_caps failed");
    return -1;
  }
  if(kernel_set_proc_rootdir(pid, kernel_get_root_vnode())) {
    klog_puts("kernel_set_proc_rootdir failed");
    return -1;
  }
  if(kernel_set_ucred_caps(pid, privcaps)) {
    klog_puts("kernel_set_ucred_caps failed");
    return -1;
  }

  if(rtld_load_sysmodule()) {
    klog_puts("load_sysmodule failed");
    return -1;
  }

  error = rtld_load();

  // restore jail and caps
  if(kernel_set_proc_rootdir(pid, rootdir)) {
    klog_puts("kernel_set_proc_rootdir failed");
    return -1;
  }
  if(kernel_set_ucred_caps(pid, caps)) {
    klog_puts("kernel_set_ucred_caps failed");
    return -1;
  }

  return error;
}


void
__rtld_fini(void) {
  rtld_lib_t* next;

  while(libhead) {
    next = libhead->next;
    rtld_close(libhead);
    libhead = next;
  }
}


void*
dlopen(const char *filename, int flags) {
  char cwd[0x1000];

  dlerrno = 0;

  if(!(flags & RTLD_MODEMASK)) {
    dlerrno = EINVAL;
    return 0;
  }
  if(flags & RTLD_GLOBAL) {
    dlerrno = ENOSYS;
    return 0;
  }
  if(flags & RTLD_TRACE) {
    dlerrno = ENOSYS;
    return 0;
  }
  if(flags & RTLD_NOW) {
    dlerrno = ENOSYS;
    return 0;
  }

  return rtld_open(getcwd(cwd, sizeof(cwd)), filename, flags);
}


void*
dlsym(void *ptr, const char *name) {
  dlerrno = 0;
  return (void*)rtld_sym((rtld_lib_t*)ptr, name);
}


int
dlclose(void *ptr) {
  dlerrno = 0;
  return rtld_close((rtld_lib_t*)ptr);
}


char*
dlerror(void) {
  if(dlerrno) {
    return _Strerror(dlerrno, 0);
  }

  return 0;
}

