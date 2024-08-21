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

#include <unistd.h>

struct passwd;

struct passwd*
getpwnam(const char *name) {
  return 0;
}


struct passwd*
getpwuid(uid_t uid) {
  return 0;
}

int
getpwnam_r(const char *name, struct passwd *pwd, char *buf, size_t buflen,
           struct passwd **result) {
    *result = 0;
    return 0;
}

int
getpwuid_r(uid_t uid, struct passwd *pwd, char *buf, size_t buflen,
           struct passwd **result) {
    *result = 0;
    return 0;
}
