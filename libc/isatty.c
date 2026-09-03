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
#include <termios.h>
#include <unistd.h>

#include <sys/ioctl.h>

#include "upty.h"


int
isatty(int fd) {
  struct termios tio;

  if(!__upty_ioctl(fd, TIOCGETA, &tio)) {
    return 1;
  }

  if(errno != EBADF) {
    errno = ENOTTY;
  }

  return 0;
}
