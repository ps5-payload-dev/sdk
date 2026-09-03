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

#include <signal.h>
#include <string.h>
#include <unistd.h>

#include "ld.h"


#define CC(t, i) ((t)->c_cc[i])
#define ISSET(t, f, b) (((t)->f & (b)) != 0)


static void
ld_emit(ld_t *ld, const void *buf, size_t len) {
  if(len) {
    ld->ops->to_remote(ld->ctx, buf, len);
  }
}


static unsigned char
ld_echo(ld_t *ld, const struct termios *t, unsigned char c) {
  unsigned char buf[2];

  if(c == '\n') {
    ld_emit(ld, "\r\n", 2);
    return 0;
  }

  if(c == '\t' || c >= 0x20) {
    ld_emit(ld, &c, 1);
    return 1;
  }

  if(c == 0x7f) {
    if(ISSET(t, c_lflag, ECHOCTL)) {
      ld_emit(ld, "^?", 2);
      return 2;
    }
    return 0;
  }

  if(ISSET(t, c_lflag, ECHOCTL)) {
    buf[0] = '^';
    buf[1] = c + 0x40;
    ld_emit(ld, buf, 2);
    return 2;
  }

  ld_emit(ld, &c, 1);

  return 1;
}


static void
ld_rubout(ld_t *ld, unsigned char cols) {
  while(cols--) {
    ld_emit(ld, "\b \b", 3);
  }
}


static void
ld_erase(ld_t *ld, const struct termios *t) {
  if(!ld->canon_len) {
    return;
  }

  ld->canon_len--;

  if(ISSET(t, c_lflag, ECHO) && ISSET(t, c_lflag, ECHOE)) {
    ld_rubout(ld, ld->width[ld->canon_len]);
  }
}


static void
ld_werase(ld_t *ld, const struct termios *t) {
  while(ld->canon_len && ld->canon[ld->canon_len - 1] == ' ') {
    ld_erase(ld, t);
  }
  while(ld->canon_len && ld->canon[ld->canon_len - 1] != ' ') {
    ld_erase(ld, t);
  }
}


static void
ld_kill(ld_t *ld, const struct termios *t) {
  while(ld->canon_len) {
    ld_erase(ld, t);
  }
}


static void
ld_flush_input(ld_t *ld) {
  ld->canon_len = 0;
}


static void
ld_commit(ld_t *ld) {
  if(ld->canon_len) {
    ld->ops->to_slave(ld->ctx, ld->canon, ld->canon_len);
    ld->canon_len = 0;
  }
}


static void
ld_push(ld_t *ld, unsigned char c, unsigned char cols) {
  if(ld->canon_len >= LD_CANON_MAX) {
    return;
  }

  ld->canon[ld->canon_len] = c;
  ld->width[ld->canon_len] = cols;
  ld->canon_len++;
}


static void
ld_input_byte(ld_t *ld, const struct termios *t, unsigned char c) {
  unsigned char cols = 0;
  int literal = ld->lnext;

  ld->lnext = 0;

  if(ISSET(t, c_iflag, ISTRIP)) {
    c &= 0x7f;
  }

  if(!literal) {
    if(c == '\r') {
      if(ISSET(t, c_iflag, IGNCR)) {
	return;
      }
      if(ISSET(t, c_iflag, ICRNL)) {
	c = '\n';
      }
    } else if(c == '\n' && ISSET(t, c_iflag, INLCR)) {
      c = '\r';
    }

    if(ISSET(t, c_lflag, ISIG)) {
      if(c == CC(t, VINTR)) {
	ld_flush_input(ld);
	if(ISSET(t, c_lflag, ECHO)) {
	  ld_echo(ld, t, c);
	  ld_emit(ld, "\r\n", 2);
	}
	ld->ops->signal(ld->ctx, SIGINT);
	return;
      }
      if(c == CC(t, VQUIT)) {
	ld_flush_input(ld);
	ld->ops->signal(ld->ctx, SIGQUIT);
	return;
      }
      if(c == CC(t, VSUSP)) {
	ld_flush_input(ld);
	ld->ops->signal(ld->ctx, SIGTSTP);
	return;
      }
    }

    if(ISSET(t, c_iflag, IXON)) {
      if(c == CC(t, VSTOP)) {
	ld->stopped = 1;
	return;
      }
      if(c == CC(t, VSTART)) {
	ld->stopped = 0;
	return;
      }
    }
  }

  /* Raw mode: no buffering, no editing. */
  if(!ISSET(t, c_lflag, ICANON)) {
    ld->ops->to_slave(ld->ctx, &c, 1);
    if(ISSET(t, c_lflag, ECHO)) {
      ld_echo(ld, t, c);
    }
    return;
  }

  if(!literal) {
    if(ISSET(t, c_lflag, IEXTEN) && c == CC(t, VLNEXT)) {
      ld->lnext = 1;
      return;
    }
    if(c == CC(t, VERASE)) {
      ld_erase(ld, t);
      return;
    }
    if(c == CC(t, VKILL)) {
      ld_kill(ld, t);
      return;
    }
    if(ISSET(t, c_lflag, IEXTEN) && c == CC(t, VWERASE)) {
      ld_werase(ld, t);
      return;
    }
    if(c == CC(t, VEOF)) {
      if(ld->canon_len) {
	ld_commit(ld);
      } else if(ld->ops->eof) {
	ld->ops->eof(ld->ctx);
      }
      return;
    }
  }

  if(ISSET(t, c_lflag, ECHO)) {
    cols = ld_echo(ld, t, c);
  } else if(c == '\n' && ISSET(t, c_lflag, ECHONL)) {
    ld_echo(ld, t, c);
  }

  ld_push(ld, c, cols);

  if(c == '\n' || (CC(t, VEOL) != _POSIX_VDISABLE && c == CC(t, VEOL))) {
    ld_commit(ld);
  }
}


void
ld_init(ld_t *ld, upty_t *pty, const ld_ops_t *ops, void *ctx) {
  memset(ld, 0, sizeof(*ld));
  ld->pty = pty;
  ld->ops = ops;
  ld->ctx = ctx;
}


void
ld_input(ld_t *ld, const void *buf, size_t len) {
  const unsigned char *p = buf;
  struct termios tio;

  upty_get_termios(ld->pty, &tio);

  for(size_t i=0; i<len; i++) {
    ld_input_byte(ld, &tio, p[i]);
  }
}


void
ld_output(ld_t *ld, const void *buf, size_t len) {
  const unsigned char *p = buf;
  unsigned char out[512];
  struct termios tio;
  size_t n = 0;

  upty_get_termios(ld->pty, &tio);

  if(!ISSET(&tio, c_oflag, OPOST)) {
    ld_emit(ld, buf, len);
    return;
  }

  for(size_t i=0; i<len; i++) {
    unsigned char c = p[i];

    if(n > sizeof(out) - 2) {
      ld_emit(ld, out, n);
      n = 0;
    }

    if(c == '\n' && ISSET(&tio, c_oflag, ONLCR)) {
      out[n++] = '\r';
      out[n++] = '\n';
    } else if(c == '\r' && ISSET(&tio, c_oflag, OCRNL)) {
      out[n++] = '\n';
    } else {
      out[n++] = c;
    }
  }

  ld_emit(ld, out, n);
}


void
ld_termios_changed(ld_t *ld) {
  struct termios tio;

  upty_get_termios(ld->pty, &tio);

  if(!ISSET(&tio, c_lflag, ICANON) && ld->canon_len) {
    ld_commit(ld);
  }
}
