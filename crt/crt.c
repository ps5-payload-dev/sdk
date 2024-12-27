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


/**
 * Dependencies provided by the ELF linker.
 **/
extern void (*__init_array_start[])(int, char**, char**, payload_args_t*) __attribute__((weak));
extern void (*__init_array_end[])(int, char**, char**, payload_args_t*) __attribute__((weak));

extern void (*__fini_array_start[])(void) __attribute__((weak));
extern void (*__fini_array_end[])(void) __attribute__((weak));

extern unsigned char __bss_start[] __attribute__((weak));
extern unsigned char __bss_end[] __attribute__((weak));


/**
 * Entry point to the main program.
 **/
extern int main(int argc, char* argv[], char *envp[]);


/**
 * Init and fini functions for crt modules.
 **/
int __syscall_init(payload_args_t* args);
int __kernel_init(payload_args_t* args);
int __klog_init(void);
int __patch_init(void);
int __rtld_init(void);
int __rtld_fini(void);
int __stacktrace_init(void);
int __stacktrace_fini(void);


/**
 * Remember the args passed to _start and the cpu state.
 **/
static payload_args_t* payload_args = 0;
static void* jmpbuf[32];


/**
 * Initialize payload runtime.
 **/
static int
payload_init(payload_args_t *args) {
  int *__isthreaded = 0;
  int error = 0;

  if((error=__syscall_init(args))) {
    return error;
  }
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
  if((error=__patch_init())) {
    klog_puts("Unable to initialize patches");
    return error;
  }
  if((error=__stacktrace_init())) {
    klog_puts("Unable to initialize stacktrace");
    return error;
  }
  if(!KERNEL_DLSYM(0x2, __isthreaded)) {
    klog_puts("Unable to resolve the symbol '__isthreaded'");
    return -1;
  }
  *__isthreaded = 1;

  return 0;
}


/**
 * Terminate the payload.
 **/
static int
payload_terminate(void) {
  void (*exit)(int) = 0;

  __stacktrace_fini();
  __rtld_fini();

  // we are running inside a hijacked process, just return
  if(kernel_dynlib_dlsym(-1, 0x2001, "sceKernelDlsym")) {
    return 0;
  }

  if(KERNEL_DLSYM(0x2, exit)) {
    exit(*payload_args->payloadout);
  }

  __builtin_trap();

  return -1;
}


/**
 *
 **/
void
payload_exit(int exit_code) {
  *payload_args->payloadout = exit_code;
  __builtin_longjmp(jmpbuf, 1);
}


/**
 *
 **/
payload_args_t*
payload_get_args(void) {
  return payload_args;
}


/**
 * Entry-point invoked by the ELF loader.
 **/
int
_start(payload_args_t *args) {
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

  payload_args = args;

  // Init payload runtime.
  if((*args->payloadout=payload_init(args))) {
    return payload_terminate();
  }

  // Obtain argc, argv and envp from libkernel.
  if((KERNEL_DLSYM(0x1, getargc) || KERNEL_DLSYM(0x2001, getargc)) &&
     (KERNEL_DLSYM(0x1, getargv) || KERNEL_DLSYM(0x2001, getargv)) &&
     (KERNEL_DLSYM(0x1, environ) || KERNEL_DLSYM(0x2001, environ))) {
    argc = getargc();
    argv = getargv();
  }

  if(!__builtin_setjmp(jmpbuf)) {
    // Run .init functions.
    count = __init_array_end - __init_array_start;
    for(int i=0; i<count; i++) {
      __init_array_start[i](argc, argv, environ, args);
    }

    // Run the actual payload.
    *args->payloadout = main(argc, argv, environ);

    // Run .fini functions.
    count = __fini_array_end - __fini_array_start;
    for(int i=0; i<count; i++) {
      __fini_array_start[count-i-1]();
    }
  }

  return payload_terminate();
}
