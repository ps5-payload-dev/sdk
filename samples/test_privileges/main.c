/* Copyright (C) 2025 John Törnblom

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

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/ptrace.h>
#include <sys/syscall.h>
#include <sys/sysctl.h>

#include <ps5/kernel.h>
#include <ps5/klog.h>
#include <ps5/mdbg.h>


#define PUTS(s) {					\
    puts(s);						\
    klog_puts(s);					\
  }

#define PRINTF(s, ...) {				\
    printf(s, __VA_ARGS__);				\
    klog_printf(s, __VA_ARGS__);			\
  }

#define PERROR(s) {							\
    printf("%s:%d:%s: %s\n", __FILE__, __LINE__, s, strerror(errno));	\
    klog_printf("%s:%d:%s: %s\n", __FILE__, __LINE__, s, strerror(errno)); \
  }


typedef struct app_info {
  uint32_t app_id;
  uint64_t unknown1;
  char     title_id[14];
  char     unknown2[0x3c];
} app_info_t;


int sceKernelGetAppInfo(pid_t pid, app_info_t *info);


static pid_t
find_pid(const char* name) {
  int mib[4] = {1, 14, 8, 0};
  pid_t mypid = getpid();
  pid_t pid = -1;
  size_t buf_size;
  uint8_t *buf;

  if(sysctl(mib, 4, 0, &buf_size, 0, 0)) {
    PERROR("sysctl");
    return -1;
  }

  if(!(buf=malloc(buf_size))) {
    PERROR("malloc");
    return -1;
  }

  if(sysctl(mib, 4, buf, &buf_size, 0, 0)) {
    PERROR("sysctl");
    free(buf);
    return -1;
  }

  for(uint8_t *ptr=buf; ptr<(buf+buf_size);) {
    int ki_structsize = *(int*)ptr;
    pid_t ki_pid = *(pid_t*)&ptr[72];
    char *ki_tdname = (char*)&ptr[447];

    ptr += ki_structsize;
    if(!strcmp(name, ki_tdname) && ki_pid != mypid) {
      pid = ki_pid;
    }
  }

  free(buf);

  return pid;
}


static char*
bin2hex(const uint8_t* bin, char* hex, size_t binsize) {
  hex[0] = '0';
  hex[1] = 'x';

  for(size_t i=0; i<binsize; ++i) {
    sprintf(&hex[i*2 + 2], "%02x", bin[i]);
  }

  hex[binsize*2 + 2] = '\0';
  
  return hex;
}


static void
print_info(pid_t pid) {
  app_info_t app_info = {0};
  uint8_t qaflags[16] = {0};
  uint8_t caps[16] = {0};
  char buf[16*3];
  
  kernel_get_qaflags(qaflags);
  kernel_get_ucred_caps(pid, caps);
  sceKernelGetAppInfo(pid, &app_info);

  PUTS("Console info");
  PUTS("------------");
  PRINTF("Firmware:       %08x\n", kernel_get_fw_version());
  PRINTF("TARGETID:       0x%02x\n", kernel_getchar(KERNEL_ADDRESS_TARGETID));
  PRINTF("SECURITY_FLAGS: 0x%02x\n", kernel_getchar(KERNEL_ADDRESS_SECURITY_FLAGS));
  PRINTF("UTOKEN_FLAGS:   0x%02x\n", kernel_getchar(KERNEL_ADDRESS_UTOKEN_FLAGS));
  PRINTF("QA_FLAGS:       %s\n", bin2hex(qaflags, buf, sizeof(qaflags)));
  PUTS("");
  
  PUTS("Privileges");
  PUTS("----------");
  PRINTF("SCE titleid:    %s\n", app_info.title_id);
  PRINTF("SCE authid:     0x%016lx\n", kernel_get_ucred_authid(pid));
  PRINTF("SCE attrs:      0x%016lx\n", kernel_get_ucred_attrs(pid));
  PRINTF("SCE caps:       %s\n", bin2hex(caps, buf, sizeof(caps)));
  PUTS("");
}


static int
test_mdbg(void) {
  intptr_t addr;
  intptr_t val;
  pid_t pid;

  if((pid=find_pid("SceRedisServer") < 0)) {
    PUTS("mdbg: fail");
    return -1;
  }

  if(!(addr=kernel_dynlib_entry_addr(pid, 0))) {
    PERROR("mdbg");
    return -1;
  }

  if(mdbg_copyout(-1, (intptr_t)&test_mdbg, &val, sizeof(val))) {
    PERROR("mdbg");
    return -1;
  }
  
  PUTS("mdbg: success");

  return 0;
}


static int
test_ptrace(void) {
  pid_t pid;

  if((pid=find_pid("SceRedisServer")) < 0) {
    PUTS("ptrace: fail");
    return -1;
  }

  if(__syscall(SYS_ptrace, PT_ATTACH, pid, 0, 0) == -1) {
    PERROR("ptrace");
    return -1;
  }

  if(__syscall(SYS_ptrace, PT_DETACH, pid, 0, 0) == -1) {
    PERROR("ptrace");
    return -1;
  }

  PUTS("ptrace: success");
      
  return 0;
}


#define ERROR_MDBG   1
#define ERROR_PTRACE 2


int
main(void) {
  int ret = 0;

  kernel_set_ucred_authid(-1, 0x4800000000010003l);
  print_info(getpid());

  PUTS("Test results");
  PUTS("------------");

  if(test_mdbg()) {
    ret |= ERROR_MDBG;
  }
  
  if(test_ptrace()) {
    ret |= ERROR_PTRACE;
  }

  return ret;
}
