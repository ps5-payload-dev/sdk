/* Copyright (C) 2026 John Törnblom

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

#pragma once

#include <sys/types.h>
#include <sys/ioctl.h>
#include <termios.h>

#define UPTY_CTL_FILENO 3

typedef struct upty upty_t;

upty_t* upty_attach(int fd);
int     upty_attach_fd(upty_t *pty, int fd);
int     upty_detach(int fd);
upty_t* upty_lookup(int fd);
int     upty_index(const upty_t *pty);
void    upty_get_termios(upty_t *pty, struct termios *tio);
void    upty_set_termios(upty_t *pty, const struct termios *tio);
void    upty_get_winsize(upty_t *pty, struct winsize *ws);
void    upty_set_winsize(upty_t *pty, const struct winsize *ws);
pid_t   upty_get_pgrp(upty_t *pty);
void    upty_set_pgrp(upty_t *pty, pid_t pgrp);

int          __upty_ioctl(int fd, unsigned long request, void *argp);
upty_t*      __upty_create(int mfd, int sfd);
void         __upty_destroy(upty_t *pty);
unsigned int __upty_gen(upty_t *pty);
void         __upty_signal(upty_t *pty, int sig);
