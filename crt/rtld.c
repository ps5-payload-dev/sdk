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
  struct rtld_lib* next;
} rtld_lib_t;


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


typedef struct sysmodtab {
  const char* name;
  unsigned int handle;
} sysmodtab_t;


/**
 * external dependencies.
 **/
static void* (*malloc)(unsigned long) = 0;
static void  (*free)(void*) = 0;
static char* (*strcat)(char*, const char*);
static int   (*strcmp)(const char*, const char*) = 0;
static int   (*strlen)(const char*) = 0;
static int   (*sprintf)(char*, const char*, ...) = 0;
static int   (*sceKernelDlsym)(int, const char*, void*) = 0;
static int   (*sceKernelLoadStartModule)(const char*, unsigned long, const void*,
					 unsigned int, void*, int*) = 0;
static int   (*sceKernelStopUnloadModule)(int, unsigned long, const void*, unsigned int,
					  const void*, void*) = 0;
static int   (*sceSysmoduleLoadModuleInternal)(unsigned int) = 0;


/**
 *
 **/
static const char*
LD_LIBRARY_PATH[] = {
  "/system/priv/lib",
  "/system/common/lib",
  "/system_ex/priv_ex/lib",
  "/system_ex/common_ex/lib",
};


/**
 *
 **/
static const sysmodtab_t sysmodtab[] = {
  {"libSceAbstractLocal.so", 0x8000005f},
  {"libSceAbstractStorage.so", 0x80000058},
  {"libSceAbstractTcs.so", 0x800000a1},
  {"libSceAbstractTwitter.so", 0x80000062},
  {"libSceAbstractYoutube.so", 0x80000061},
  {"libSceAc3Enc.so", 0x80000013},
  {"libSceAgc.so", 0x80000094},
  {"libSceAgcDriver.so", 0x80000080},
  {"libSceAgcResourceRegistration.so", 0x80000093},
  {"libSceAgcVsh.so", 0x80000086},
  {"libSceAgcVshDebug.so", 0x80000087},
  {"libSceAjm.native.so", 0x80000023},
  {"libSceAjmi.so", 0x8000007e},
  {"libSceAmpr.so", 0x800000b7},
  {"libSceAppChecker.so", 0x80000032},
  {"libSceAppDbShellCoreClient.so", 0x800000a7},
  {"libSceAppInstUtil.so", 0x80000014},
  {"libSceAsyncStorageInternal.so", 0x80000077},
  {"libSceAudioIn.so", 0x80000002},
  {"libSceAudioOut.so", 0x80000001},
  {"libSceAudioSystem.so", 0x80000083},
  {"libSceAudiodecCpuDtsHdMa.so", 0x8000002d},
  {"libSceAudiodecCpuLpcm.so", 0x8000002e},
  {"libSceAudiodecCpuTrhd.so", 0x80000082},
  {"libSceAvSetting.so", 0x80000021},
  {"libSceAvcap2.so", 0x80000085},
  {"libSceBackupRestoreUtil.so", 0x8000003f},
  {"libSceBgft.so", 0x8000002a},
  {"libSceBgsStorage.so", 0x800000a3},
  {"libSceCamera.so", 0x8000001a},
  {"libSceCdlgUtilServer.so", 0x80000007},
  {"libSceCommonDialog.so", 0x80000018},
  {"libSceComposite.so", 0x8000008a},
  {"libSceCompositeExt.so", 0x8000008b},
  {"libSceContentListController.so", 0x800000ad},
  {"libSceDataTransfer.so", 0x80000057},
  {"libSceDbg.so", 0x80000025},
  {"libSceDipsw.so", 0x80000029},
  {"libSceDseehx.so", 0x80000056},
  {"libSceDtsEnc.so", 0x80000028},
  {"libSceEmbeddedTts.so", 0x8000009c},
  {"libSceEmbeddedTtsCoreG3.so", 0x8000009b},
  {"libSceFsInternalForVsh.so", 0x80000066},
  {"libSceGLSlimVSH.so", 0x800000a9},
  {"libSceGifParser.so", 0x8000005e},
  {"libSceGpuCapture.so", 0x8000007f},
  {"libSceGpuTrace.so", 0x8000007b},
  {"libSceGvMp4Parser.so", 0x8000005c},
  {"libSceHidControl.so", 0x80000017},
  {"libSceHttp.so", 0x8000000a},
  {"libSceHttp2.so", 0x8000008c},
  {"libSceHttpCache.so", 0x80000078},
  {"libSceIcu.so", 0x800000a8},
  {"libSceIdu.so", 0x800000a6},
  {"libSceImageUtil.so", 0x80000059},
  {"libSceIpmi.so", 0x8000001d},
  {"libSceJemspace.so", 0x8000009e},
  {"libSceJitBridge.so", 0x8000006f},
  {"libSceJpegParser.so", 0x8000005b},
  {"libSceJsc.so", 0x800000b0},
  {"libSceJscCompiler.so", 0x80000070},
  {"libSceJxr.so", 0x800000b4},
  {"libSceJxrParser.so", 0x800000b5},
  {"libSceKbEmulate.so", 0x80000031},
  {"libSceLibreSsl.so", 0x80000065},
  {"libSceLibreSsl3.so", 0x800000b8},
  {"libSceLoginMgrServer.so", 0x80000045},
  {"libSceMarlin.so", 0x80000027},
  {"libSceMat.so", 0x80000048},
  {"libSceMbus.so", 0x8000001e},
  {"libSceMediaFrameworkInterface.so", 0x80000095},
  {"libSceMediaFrameworkUtil.so", 0x800000b6},
  {"libSceMetadataReaderWriter.so", 0x8000005a},
  {"libSceNKWeb.so", 0x80000079},
  {"libSceNKWebKit.so", 0x8000007a},
  {"libSceNet.so", 0x8000001c},
  {"libSceNetCtl.so", 0x80000009},
  {"libSceNgs2.so", 0x80000090},
  {"libSceNpCommon.so", 0x8000000c},
  {"libSceNpGameIntent.so", 0x8000008d},
  {"libSceNpManager.so", 0x8000000d},
  {"libSceNpRemotePlaySessionSignaling.so", 0x8000009a},
  {"libSceNpSns.so", 0x8000001b},
  {"libSceNpTcs.so", 0x800000a0},
  {"libSceNpWebApi.so", 0x8000000e},
  {"libSceNpWebApi2.so", 0x8000008f},
  {"libSceOpusCeltDec.so", 0x80000044},
  {"libSceOpusCeltEnc.so", 0x80000043},
  {"libSceOpusDec.so", 0x80000069},
  {"libSceOpusSilkEnc.so", 0x80000068},
  {"libSceOrbisCompat.so", 0x80000071},
  {"libScePad.so", 0x80000024},
  {"libScePngParser.so", 0x8000005d},
  {"libScePosixForWebKit.so", 0x80000098},
  {"libScePsm.so", 0x80000030},
  {"libSceRazorCpu_debug.so", 0x80000075},
  {"libSceRegMgr.so", 0x8000001f},
  {"libSceRemotePlayClientIpc.so", 0x800000b9},
  {"libSceResourceArbitrator.so", 0x80000092},
  {"libSceRnpsAppMgr.so", 0x80000076},
  {"libSceRtc.so", 0x80000020},
  {"libSceSaveData.so", 0x8000000f},
  {"libSceShareInternal.native.so", 0x8000008e},
  {"libSceSocialScreen.so", 0x800000ae},
  {"libSceSsl.so", 0x8000000b},
  {"libSceSulphaDrv.so", 0x8000003b},
  {"libSceSysCore.so", 0x80000004},
  {"libSceSysUtil.so", 0x80000026},
  {"libSceSystemLogger2.so", 0x800000b3},
  {"libSceSystemLogger2Delivery.so", 0x80000089},
  {"libSceSystemLogger2Game.so", 0x8000009f},
  {"libSceSystemLogger2NativeQueueClient.so", 0x80000088},
  {"libSceSystemService.so", 0x80000010},
  {"libSceSystemTts.so", 0x80000097},
  {"libSceTEEClient.so", 0x800000a2},
  {"libSceUserService.so", 0x80000011},
  {"libSceVcodec.so", 0x80000091},
  {"libSceVdecCore.native.so", 0x80000015},
  {"libSceVdecSavc2.native.so", 0x80000036},
  {"libSceVdecShevc.native.so", 0x8000003c},
  {"libSceVdecSvp9.native.so", 0x800000af},
  {"libSceVenc.so", 0x80000084},
  {"libSceVideoOut.so", 0x80000022},
  {"libSceVideoOutSecondary.so", 0x80000046},
  {"libSceVideoStreamingEngine_sys.so", 0x800000b2},
  {"libSceVisionManager.so", 0x80000012},
  {"libSceVnaInternal.so", 0x8000007c},
  {"libSceVnaWebsocket.so", 0x8000007d},
  {"libSceVoiceCommand.so", 0x80000099},
  {"libSceWeb.so", 0x80000072},
  {"libSceWebKit2.so", 0x80000073},
  {"libSceWebKit2Secure.so", 0x80000074},
  {"libSceWebmParserMdrw.so", 0x800000a4},
  {"libcairo.so", 0x800000ac},
  {"libcurl.so", 0x800000b1},
  {"libicu.so", 0x800000aa},
  {"libpng16.so", 0x800000ab}
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
 *
 **/
static rtld_lib_t*
rtld_open(const char* basename) {
  rtld_lib_t *lib = 0;
  char filename[255];
  int handle = 0;

  if(!strcmp(basename, "libkernel.so") ||
     !strcmp(basename, "libkernel_web.so") ||
     !strcmp(basename, "libkernel_sys.so") ||
     !strcmp(basename, "libpthread.so")) {
    lib           = malloc(sizeof(rtld_lib_t));
    lib->handle   = libkernel_handle;
    lib->next     = 0;
    return lib;
  }

  if(!strcmp(basename, "libSceLibcInternal.so")) {
    lib           = malloc(sizeof(rtld_lib_t));
    lib->handle   = 0x2;
    lib->next     = 0;
    return lib;
  }

  for(int i=0; i<sizeof(LD_LIBRARY_PATH)/sizeof(LD_LIBRARY_PATH[0]); i++) {
    sprintf(filename, "%s/%s", LD_LIBRARY_PATH[i], basename);
    filename[strlen(filename)-2] = 0;
    strcat(filename, "sprx");
    if(syscall(SYS_access, filename, 0) < 0) {
      continue;
    }

    // sysmodules needs to be loaded internally first
    for(int i=0; i<sizeof(sysmodtab)/sizeof(sysmodtab[0]); i++) {
      if(!strcmp(basename, sysmodtab[i].name)) {
	if(sceSysmoduleLoadModuleInternal(sysmodtab[i].handle)) {
	  klog_perror("sceSysmoduleLoadModuleInternal");
	  return 0;
	}
      }
    }

    if((handle=sceKernelLoadStartModule(filename, 0, 0, 0, 0, 0)) > 0) {
      break;
    }
  }

  if(handle <= 0) {
    return 0;
  }

  lib         = malloc(sizeof(rtld_lib_t));
  lib->handle = handle;
  lib->next   = 0;
  
  return lib;
}


/**
 *
 **/
static unsigned long
rtld_sym(rtld_lib_t* lib, const char* name) {
  unsigned long addr = 0;

  sceKernelDlsym(lib->handle, name, &addr);

  return addr;
}


/**
 *
 **/
static int __attribute__((used))
rtld_close(rtld_lib_t* lib) {
  int handle = lib->handle;

  free(lib);

  return sceKernelStopUnloadModule(handle, 0, 0, 0, 0, 0);
}


/**
 *
 **/
static int
dt_needed(const char* basename) {
  rtld_lib_t* lib;

  if((lib=rtld_open(basename))) {
    lib->next = libhead;
    libhead = lib;
    return 0;
  }

  klog_libload_error(basename);

  // FIXME: ignoring errors when loading libScePosixForWebKit
  if(!strcmp(basename, "libScePosixForWebKit.so")) {
    return 0;
  }

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

