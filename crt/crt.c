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


int __klog_init(payload_args_t *args);
int __kernel_init(payload_args_t* args);
int __rtld_init(payload_args_t* args);

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

  if((error=args->sceKernelDlsym(0x2, "__isthreaded", &__isthreaded))) {
    return error;
  }
  *__isthreaded = 1;

  if(args->sceKernelDlsym(0x1, "getpid", &ptr_syscall)) {
    if((error=args->sceKernelDlsym(0x2001, "getpid", &ptr_syscall))) {
      return error;
    }
  }
  // jump directly to the syscall instruction
  // in getpid (provided by libkernel)
  ptr_syscall += 0xa;

  if((error=__klog_init(args))) {
    return error;
  }
  if((error=__kernel_init(args))) {
    return error;
  }
  if((error=__rtld_init(args))) {
    return error;
  }

  return 0;
}


/**
 * Terminate the payload.
 **/
static void
terminate(void) {
  void (*exit)(int) = 0;
  long dummy;

  // we are running inside a hijacked process, just return
  if(payload_args->sceKernelDlsym(0x1, "sceKernelDlsym", &dummy)) {
    return;
  }

  if(!payload_args->sceKernelDlsym(0x2, "exit", &exit)) {
    exit(*payload_args->payloadout);
  }
}



/**
 * Entry-point invoked by the ELF loader.
 **/
void
_start(payload_args_t *args) {
  char** (*getargv)(void) = 0;
  int (*getargc)(void) = 0;
  unsigned long count = 0;
  char** envp = 0;
  char** argv = 0;
  int argc = 0;

  // Clear .bss section.
  for(unsigned char* bss=__bss_start; bss<__bss_end; bss++) {
    *bss = 0;
  }

  // Init runtime
  payload_args = args;
  *args->payloadout = 0;
  if((*args->payloadout=pre_init(args))) {
    terminate();
    return;
  }

  // Obtain argc, argv and envp from libkernel
  if((!args->sceKernelDlsym(0x1, "getargc", &getargc) ||
      !args->sceKernelDlsym(0x2001, "getargc", &getargc)) &&
     (!args->sceKernelDlsym(0x1, "getargv", &getargv) ||
      !args->sceKernelDlsym(0x2001, "getargv", &getargv))) {
    argc = getargc();
    argv = getargv();
  }
  if(args->sceKernelDlsym(0x1, "environ", &envp)) {
    if(args->sceKernelDlsym(0x2001, "environ", &envp)) {
      envp = 0;
    }
  }

  // Run .init functions.
  count = __init_array_end - __init_array_start;
  for(int i=0; i<count; i++) {
    __init_array_start[i](argc, argv, envp);
  }

  // Run the actual payload
  *args->payloadout = main(argc, argv, envp);

  // Run .fini functions.
  count = __fini_array_end - __fini_array_start;
  for(int i=0; i<count; i++) {
    __fini_array_start[count-i-1]();
  }

  terminate();
}
