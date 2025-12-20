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

#include <stdio.h>


int sceAppInstUtilInitialize(void);
int sceAppInstUtilAppInstallTitleDir(const char*, const char*, void*);


int
main(int argc, char *argv[]) {
  int err;

  if((err=sceAppInstUtilInitialize())) {
    printf("sceAppInstUtilInitialize: %x\n", err);
    return -1;
  }

  if((err=sceAppInstUtilAppInstallTitleDir(TITLE_ID, "/user/app/", 0))) {
    printf("sceAppInstUtilAppInstallTitleDir: %x\n", err);
    return -1;
  }

  return 0;
}
