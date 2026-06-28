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

#include <errno.h>
#include <grp.h>

#include <sys/types.h>

struct group*
getgrnam(const char *name) {
#warning "getgrnam() not implemented"
  return 0;
}


struct group*
getgrgid(gid_t gid) {
#warning "getgrgid() not implemented"
  return 0;
}


int
getgrnam_r(const char *name, struct group *grp, char* buf, size_t buflen,
	   struct group **result) {
#warning "getgrnam_r() not implemented"
  *result = 0;
  return ENOSYS;
}


int
getgrgid_r(gid_t gid, struct group *grp, char *buf, size_t buflen,
	   struct group **result) {
#warning "getgrgid_r() not implemented"
  *result = 0;
  return ENOSYS;
}
