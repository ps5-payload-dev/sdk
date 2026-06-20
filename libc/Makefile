#   Copyright (C) 2024 John Törnblom
#
# This file is free software; you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; see the file COPYING. If not see
# <http://www.gnu.org/licenses/>.

include ../common.mk

CFLAGS := -target x86_64-sie-ps5 -fPIC  -fno-plt -fno-stack-protector
CFLAGS += -nobuiltininc -isystem ../include/freebsd
CFLAGS += -fvisibility-nodllstorageclass=default
CFLAGS += -O1

ASFLAGS := $(CFLAGS)

SRCS := $(wildcard *.c)
OBJS := $(SRCS:.c=.o) _setjmp.o

.PHONY: all clean install

all: libc.a libdl.a libpthread.a

libc.a: $(OBJS)
	$(AR) -rsc $@ $^

libdl.a:
	$(AR) -rsc $@

libpthread.a:
	$(AR) -rsc $@

clean:
	rm -f *.a *.o

install: libc.a libdl.a libpthread.a
	install -d $(DESTDIR)/target/lib
	install libc.a $(DESTDIR)/target/lib
	install libdl.a $(DESTDIR)/target/lib
	install libpthread.a $(DESTDIR)/target/lib
