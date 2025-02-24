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
#include "payload.h"

#define DLSYM(handle, sym) (sym=(void*)kernel_dynlib_dlsym(-1, handle, #sym))

#define EINVAL 22

/**
 * Dependencies provided by the ELF linker.
 **/
extern void (*__init_array_start[])(int, char**, char**) __attribute__((weak));
extern void (*__init_array_end[])(int, char**, char**) __attribute__((weak));

extern void (*__fini_array_start[])(void) __attribute__((weak));
extern void (*__fini_array_end[])(void) __attribute__((weak));

extern unsigned char __bss_start[] __attribute__((weak));
extern unsigned char __bss_end[] __attribute__((weak));


/**
 * Entry point to the main program.
 **/
extern int main(int argc, char* argv[], char *envp[]);


int __kernel_init(payload_args_t* args);
int __klog_init(void);
int __rtld_init(void);
int __rtld_fini(void);


static payload_args_t* payload_args = 0;

payload_args_t*
payload_get_args(void) {
  return payload_args;
}


static __attribute__ ((used)) long ptr_syscall = 0;

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


static int
pre_init(payload_args_t *args) {
  int *__isthreaded;
  int error = 0;

  if((error=__kernel_init(args))) {
    return error;
  }
  if((error=__klog_init())) {
    return error;
  }
  if((error=__rtld_init())) {
    klog_puts("Unable to initialize rtld");
    return error;
  }
  if(!DLSYM(0x2, __isthreaded)) {
    klog_puts("Unable to resolve the symbol '__isthreaded'");
    return -1;
  }
  *__isthreaded = 1;

  return 0;
}


/**
 * Terminate the payload.
 **/
static void
terminate(void) {
  void (*exit)(int) = 0;

  __rtld_fini();

  // we are running inside a hijacked process, just return
  if(kernel_dynlib_dlsym(-1, 0x2001, "sceKernelDlsym")) {
    klog_puts("we are running inside a hijacked process, just return");
    return;
  }

  if(DLSYM(0x2, exit)) {
    exit(*payload_args->payloadout);
  }
}


/**
 * Entry-point invoked by the ELF loader.
 **/
void
_start(payload_args_t *args) {
  int (*sceKernelDlsym)(int, const char*, void*) = 0;
  char** (*getargv)(void) = 0;
  int (*getargc)(void) = 0;
  unsigned long count = 0;
  char** environ = 0;
  char** argv = 0;
  int argc = 0;

  // Clear .bss section.
  for(unsigned char* bss=__bss_start; bss<__bss_end; bss++) {
    *bss = 0;
  }

  // Init runtime
  payload_args = args;
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

  if(!ptr_syscall) {
    *args->payloadout = -EINVAL;
    return;
  }

  ptr_syscall += 0xa; // jump directly to the syscall instruction

  if((*args->payloadout=pre_init(args))) {
    terminate();
    return;
  }

  // Obtain argc, argv and envp from libkernel
  if((DLSYM(0x1, getargc) || DLSYM(0x2001, getargc)) &&
     (DLSYM(0x1, getargv) || DLSYM(0x2001, getargv)) &&
     (DLSYM(0x1, environ) || DLSYM(0x2001, environ))) {
    argc = getargc();
    argv = getargv();
  }

  // Run .init functions.
  count = __init_array_end - __init_array_start;
  for(int i=0; i<count; i++) {
    __init_array_start[i](argc, argv, environ);
  }

  // Run the actual payload.
  *args->payloadout = main(argc, argv, environ);

  // Run .fini functions.
  count = __fini_array_end - __fini_array_start;
  for(int i=0; i<count; i++) {
    __fini_array_start[count-i-1]();
  }

  terminate();
}
