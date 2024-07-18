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


#define ELF64_R_SYM(info) ((info) >> 32)

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
extern Elf64_Dyn _DYNAMIC[];


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
static char* (*strcat)(char*, const char*);
static char* (*strcpy)(char*, const char*);
static int   (*strcmp)(const char*, const char*) = 0;
static int   (*strlen)(const char*) = 0;
static int   (*sprintf)(char*, const char*, ...) = 0;
static char* (*getcwd)(char*, unsigned long) = 0;
static char* (*_Strerror)(int, char*) = 0;
static int   (*sceKernelDlsym)(int, const char*, void*) = 0;
static int   (*sceKernelLoadStartModule)(const char*, unsigned long, const void*,
					 unsigned int, void*, int*) = 0;
static int   (*sceKernelStopUnloadModule)(int, unsigned long, const void*, unsigned int,
					  const void*, void*) = 0;
static int   (*sceSysmoduleLoadModuleInternal)(unsigned int) = 0;


/**
 *
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
 *
 **/
static void
klog_resolve_error(const char *name) {
  klog_printf("Unable to resolve the symbol '%s'\n", name);
}


/**
 *
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
 * Replace .so suffix with .sprx
 **/
static void
rtld_so2sprx(const char* filename, char* sprx) {
  int len = strlen(filename);

  strcpy(sprx, filename);
  if(len >= 3 && !strcmp(sprx+len-3, ".so")) {
    sprx[len-2] = 0;
    strcat(sprx, "sprx");
  }
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
  if(!syscall(SYS_access, path, 0)) {
    return 0;
  }

  sprintf(path, "/system/priv/lib/%s", filename);
  if(!syscall(SYS_access, path, 0)) {
      return 0;
  }

  sprintf(path, "/system/common/lib/%s", filename);
  if(!syscall(SYS_access, path, 0)) {
      return 0;
  }

  sprintf(path, "/system_ex/priv_ex/lib/%s", filename);
  if(!syscall(SYS_access, path, 0)) {
      return 0;
  }

  sprintf(path, "/system_ex/common_ex/lib/%s", filename);
  if(!syscall(SYS_access, path, 0)) {
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
  lib->handle = handle;
  lib->flags = flags;
  lib->next = 0;
  return lib;
}


/**
 *
 **/
static rtld_lib_t*
rtld_open(const char* cwd, const char* filename, int flags) {
  const char *basename = rtld_basename(filename);
  char path[0x4000];
  int handle;
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

  if(rtld_find_sprx(cwd, filename, path)) {
    dlerrno = ENOENT;
    return 0;
  }

  if(flags & RTLD_NOLOAD) { // TODO
    dlerrno = ENOSYS;
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
  int error;

  if((error=sceKernelDlsym(lib->handle, name, &addr))) {
    dlerrno = error;
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
dt_needed(const char* basename) {
  char sprx[0x1000];
  rtld_lib_t* lib;

  rtld_so2sprx(basename, sprx);
  if((lib=rtld_open(0, sprx, RTLD_LAZY))) {
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
rtld_load_sysmodule(payload_args_t *args) {
  int pid = syscall(SYS_getpid);
  unsigned int handle;

  if(kernel_dynlib_handle(pid, "libSceSysmodule.sprx", &handle)) {
    if((handle=sceKernelLoadStartModule("/system/common/lib/libSceSysmodule.sprx",
					0, 0, 0, 0, 0)) <= 0) {
      klog_libload_error("libSceSysmodule.sprx");
      return -1;
    }
  }

  // resolve sceSysmoduleLoadModuleInternal
  return args->sceKernelDlsym(handle, "sceSysmoduleLoadModuleInternal",
			      &sceSysmoduleLoadModuleInternal);
}


int
__rtld_init(payload_args_t *args) {
  static const unsigned char privcaps[16] = {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
					     0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
  int pid = syscall(SYS_getpid);
  unsigned long rootdir = 0;
  unsigned char caps[16];
  int error = 0;

  // determine libkernel handle
  if(!args->sceKernelDlsym(0x1, "sceKernelDlsym", &sceKernelDlsym)) {
    libkernel_handle = 0x1;
  } else if(!args->sceKernelDlsym(0x2001, "sceKernelDlsym", &sceKernelDlsym)) {
    libkernel_handle = 0x2001;
  } else {
    klog_puts("Unable to determine libkernel handle");
    return -1;
  }

  // load deps to libc
  if((error=args->sceKernelDlsym(0x2, "malloc", &malloc))) {
    klog_resolve_error("malloc");
    return error;
  }
  if((error=args->sceKernelDlsym(0x2, "free", &free))) {
    klog_resolve_error("free");
    return error;
  }
  if((error=args->sceKernelDlsym(0x2, "strcat", &strcat))) {
    klog_resolve_error("strcat");
    return error;
  }
  if((error=args->sceKernelDlsym(0x2, "strcpy", &strcpy))) {
    klog_resolve_error("strcpy");
    return error;
  }
  if((error=args->sceKernelDlsym(0x2, "strcmp", &strcmp))) {
    klog_resolve_error("strcmp");
    return error;
  }
  if((error=args->sceKernelDlsym(0x2, "strlen", &strlen))) {
    klog_resolve_error("strlen");
    return error;
  }
  if((error=args->sceKernelDlsym(0x2, "sprintf", &sprintf))) {
    klog_resolve_error("sprintf");
    return error;
  }
  if((error=args->sceKernelDlsym(0x2, "getcwd", &getcwd))) {
    klog_resolve_error("getcwd");
    return error;
  }
  if((error=args->sceKernelDlsym(0x2, "_Strerror", &_Strerror))) {
    klog_resolve_error("_Strerror");
    return error;
  }

  // load deps to libkernel
  if((error=args->sceKernelDlsym(libkernel_handle, "sceKernelDlsym",
				 &sceKernelDlsym))) {
    klog_resolve_error("sceKernelDlsym");
    return error;
  }
  if((error=args->sceKernelDlsym(libkernel_handle, "sceKernelLoadStartModule",
				 &sceKernelLoadStartModule))) {
    klog_resolve_error("sceKernelLoadStartModule");
    return error;
  }
  if((error=args->sceKernelDlsym(libkernel_handle, "sceKernelStopUnloadModule",
				 &sceKernelStopUnloadModule))) {
    klog_resolve_error("sceKernelStopUnloadModule");
    return error;
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

  if(rtld_load_sysmodule(args)) {
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


void*
dlopen(const char *filename, int flags) {
  char sprx[0x1000];
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

  rtld_so2sprx(filename, sprx);
  return rtld_open(getcwd(cwd, sizeof(cwd)), sprx, flags);
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

