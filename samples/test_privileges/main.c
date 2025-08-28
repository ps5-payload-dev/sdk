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

#include <sys/mman.h>
#include <sys/ptrace.h>
#include <sys/syscall.h>
#include <sys/sysctl.h>
#include <sys/wait.h>

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


static int
sys_ptrace(int request, pid_t pid, caddr_t addr, int data) {
  uint8_t privcaps[16] = {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
                          0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
  pid_t mypid = getpid();
  uint8_t caps[16];
  uint64_t authid;
  int ret;

  if(!(authid=kernel_get_ucred_authid(mypid))) {
    return -1;
  }
  if(kernel_get_ucred_caps(mypid, caps)) {
    return -1;
  }

  if(kernel_set_ucred_authid(mypid, 0x4800000000010003l)) {
    return -1;
  }
  if(kernel_set_ucred_caps(mypid, privcaps)) {
    return -1;
  }

  ret = (int)__syscall(SYS_ptrace, request, pid, addr, data);

  if(kernel_set_ucred_authid(mypid, authid)) {
    return -1;
  }
  if(kernel_set_ucred_caps(mypid, caps)) {
    return -1;
  }

  return ret;
}


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
  PRINTF("uid:            %d\n", getuid());
  PRINTF("euid:           %d\n", geteuid());
  PRINTF("jail vnode:     0x%lx\n", kernel_get_proc_jaildir(pid));
  PUTS("");
}


static int
test_mdbg(void) {
  intptr_t val = -1;
  intptr_t addr;
  pid_t pid;
  int prot;

  if((pid=find_pid("SceRedisServer")) < 0) {
    PUTS("mdbg: find_pid failed");
    return -1;
  }

  if(!(addr=kernel_dynlib_entry_addr(pid, 0))) {
    PERROR("mdbg kernel_dynlib_entry_add");
    return -1;
  }

  if(mdbg_copyout(pid, addr, &val, sizeof(val))) {
    PERROR("mdbg_copyout");
    return -1;
  } else {
    PUTS("mdbg_copyout: success");
  }

  if((prot=kernel_get_vmem_protection(pid, addr, sizeof(val))) < 0) {
    PUTS("mdbg: kernel_get_vmem_protection failed");
    return -1;
  }

  if(kernel_set_vmem_protection(pid, addr, sizeof(val), prot | PROT_READ | PROT_WRITE)) {
    PUTS("mdbg: kernel_set_vmem_protection failed");
    return -1;
  }

  if(mdbg_copyin(pid, &val, addr, sizeof(val))) {
    PERROR("mdbg_copyin");
    kernel_set_vmem_protection(pid, addr, sizeof(val), prot);
    return -1;
  } else {
    PUTS("mdbg_copyin: success");
  }

  if(kernel_set_vmem_protection(pid, addr, sizeof(val), prot)) {
    PUTS("mdbg: kernel_set_vmem_protection failed");
    return -1;
  }

  return 0;
}


static int
test_ptrace(void) {
  struct ptrace_io_desc iod = {0};
  intptr_t val = -1;
  intptr_t addr;
  int err = 0;
  int prot;
  pid_t pid;

  if((pid=find_pid("SceRedisServer")) < 0) {
    PUTS("ptrace: fail");
    return -1;
  }

  if(sys_ptrace(PT_ATTACH, pid, 0, 0)) {
    PERROR("ptrace attach");
    return -1;
  } else {
    PUTS("ptrace attach: success");
  }

  if(waitpid(pid, 0, 0) == -1) {
    perror("ptrace waitpid");
    return -1;
  }

  if(!(addr=kernel_dynlib_entry_addr(pid, 0))) {
    perror("ptrace kernel_dynlib_entry_addr");
    err = -1;
  }

  prot = kernel_get_vmem_protection(pid, addr, sizeof(val));
  kernel_set_vmem_protection(pid, addr, sizeof(val), prot | PROT_READ | PROT_WRITE);

  iod.piod_op = PIOD_READ_D;
  iod.piod_offs = (void*)addr;
  iod.piod_addr = &val;
  iod.piod_len = sizeof(val);
  if(sys_ptrace(PT_IO, pid, (caddr_t)&iod, 0)) {
    PERROR("ptrace io read");
    err = -1;
  } else {
    PUTS("ptrace io read: success");
  }

  iod.piod_op = PIOD_WRITE_D;
  iod.piod_offs = (void*)addr;
  iod.piod_addr = &val;
  iod.piod_len = sizeof(val);
  if(sys_ptrace(PT_IO, pid, (caddr_t)&iod, 0)) {
    PERROR("ptrace io write");
    err = -1;
  } else {
    PUTS("ptrace io write: success");
  }

  kernel_set_vmem_protection(pid, addr, sizeof(val), prot);

  if(sys_ptrace(PT_DETACH, pid, 0, 0)) {
    PERROR("ptrace detach");
    err = -1;
  } else {
    PUTS("ptrace detach: success");
  }

  return err;
}


#define ERROR_MDBG   1
#define ERROR_PTRACE 2


int
main(void) {
  int ret = 0;

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
