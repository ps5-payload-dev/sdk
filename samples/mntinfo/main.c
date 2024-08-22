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


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mount.h>


/**
 * Print all mount points to stdout.
 **/
int
main(void) {
  struct statfs *buf = 0;
  int nitems = 0;

  if((nitems=getmntinfo(&buf, MNT_WAIT)) < 0) {
    return EXIT_FAILURE;
  }

  for(int i=0; i<nitems; i++) {
    printf("%s on %s (%s, flags=0x%lx)\n",
	   buf[i].f_mntfromname,
	   buf[i].f_mntonname,
	   buf[i].f_fstypename,
	   buf[i].f_flags);
  }

  free(buf);

  return EXIT_SUCCESS;
}
