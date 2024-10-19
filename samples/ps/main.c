/* Copyright (C) 2023 John Törnblom

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


#include <sys/types.h>
#include <sys/proc.h>
#include <sys/user.h>
#include <sys/sysctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ps5/kernel.h>


typedef struct app_info {
  uint32_t app_id;
  uint64_t unknown1;
  uint32_t app_type;
  char     title_id[10];
  char     unknown2[0x3c];
} app_info_t;


int sceKernelGetAppInfo(pid_t pid, app_info_t *info);


static char *state_abbrev[] = {
  "", "START", "RUN\0\0\0", "SLEEP", "STOP", "ZOMB", "WAIT", "LOCK"
};


#define MiB(x) ((x) / (1024.0 * 1024))

int
main() {
  int mib[4] = {CTL_KERN, KERN_PROC, KERN_PROC_PROC, 0};
  app_info_t appinfo;
  size_t buf_size;
  void *buf;

  // determine size of query response
  if(sysctl(mib, 4, NULL, &buf_size, NULL, 0)) {
    perror("sysctl");
    return -1;
  }

  // allocate memory for query response
  if(!(buf=malloc(buf_size))) {
    perror("malloc");
    return -1;
  }

  // query the kernel for proc info
  if(sysctl(mib, 4, buf, &buf_size, NULL, 0)) {
    perror("sysctl");
    free(buf);
    return -1;
  }


  printf("\n     PID      PPID     PGID      SID      UID           AuthId"
        "      State  AppId  TitleId     Memory (MiB)  Command\n");
  for(void *ptr=buf; ptr<(buf+buf_size);) {
    struct kinfo_proc *ki = (struct kinfo_proc*)ptr;
    ptr += ki->ki_structsize;

    if(sceKernelGetAppInfo(ki->ki_pid, &appinfo)) {
      memset(&appinfo, 0, sizeof(appinfo));
    }

    printf("%8u  %8u %8u %8u %8u %016lx %10s   %04x  %s  %6.1f / %6.1f  %s\n",
	   ki->ki_pid, ki->ki_ppid, ki->ki_pgid, ki->ki_sid,
	   ki->ki_uid, kernel_get_ucred_authid(ki->ki_pid),
           state_abbrev[(int)ki->ki_stat], appinfo.app_id,
	   appinfo.title_id, MiB(ki->ki_rssize * PAGE_SIZE),
           MiB(ki->ki_size), ki->ki_comm);
  }

  free(buf);

  return 0;
}

