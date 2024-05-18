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
#include <fcntl.h>
#include <unistd.h>


int
pipe2(int pipefd[2], int flags) {
  int fd[2];
  int ret;
  int err;

  if((ret=pipe(fd))) {
    return ret;
  }

  if(flags & O_CLOEXEC) {
    if(!(ret=fcntl(fd[0], F_SETFD, FD_CLOEXEC))) {
      ret = fcntl(fd[1], F_SETFD, FD_CLOEXEC);
    }
  }

  if(flags & O_NONBLOCK && !ret) {
    if(!(ret=fcntl(fd[0], F_SETFL, O_NONBLOCK))) {
      ret = fcntl(fd[1], F_SETFL, O_NONBLOCK);
    }
  }

  if(ret) {
    err = errno;
    close(fd[0]);
    close(fd[1]);
    errno = err;
  } else {
    pipefd[0] = fd[0];
    pipefd[1] = fd[1];
  }

  return ret;
}
