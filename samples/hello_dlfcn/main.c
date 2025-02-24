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

#include <dlfcn.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>


int (*sceRandomGetRandomNumber)(uint8_t* buf, size_t size) = 0;


static void
hexdump(uint8_t* buf, size_t size) {
  for(int i=0; i<size; i++) {
    if(i%16 == 0 && i!= 0) {
      printf("\n");
    }
    printf("%02x ", buf[i]);
  }
  printf("\n");
}


static void
random_hexdump(uint8_t* buf, size_t size) {

  memset(buf, 0, size);
  if(!sceRandomGetRandomNumber(buf, size)) {
    hexdump(buf, size);
  }
}


int main() {
  void* libSceRandom;
  uint8_t buf[0x40];

  if(!(libSceRandom=dlopen("libSceRandom.sprx", RTLD_LAZY))) {
    puts(dlerror());
    return -1;
  }

  if(!(sceRandomGetRandomNumber=dlsym(libSceRandom, "sceRandomGetRandomNumber"))) {
    puts(dlerror());
  } else {
    random_hexdump(buf, sizeof(buf));
  }
  
  if(dlclose(libSceRandom)) {
    puts(dlerror());
    return -1;
  }
  
  return 0;
}
