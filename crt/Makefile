#   Copyright (C) 2023 John Törnblom
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

CC      ?= cc
CFLAGS  := -ffreestanding -fno-builtin -nostdlib -mcmodel=large -static -masm=intel
DESTDIR ?= /opt/ps5-payload-sdk

all: crt1.o

crt1.o: crt.o kernel.o
	$(LD) -o $@ -r $^

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $^

clean:
	rm -f *.o

install: crt1.o
	install -d $(DESTDIR)/usr/lib
	install crt1.o $(DESTDIR)/usr/lib