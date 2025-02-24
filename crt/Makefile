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

DESTDIR ?= /opt/ps5-payload-sdk

CCS := clang-18 clang-17 clang-16 clang-15 clang
CCS := $(foreach CC,$(CCS),$(if $(shell command -v $(CC) 2> /dev/null),$(CC)))
CC  := $(firstword $(CCS))
ifndef CC
    $(error No suitable compiler found)
endif

LDS := ld.lld-18 ld.lld-17 ld.lld-16 ld.lld-15 ld.lld
LDS := $(foreach LD,$(LDS),$(if $(shell command -v $(LD) 2> /dev/null),$(LD)))
LD  := $(firstword $(LDS))
ifndef LD
    $(error No suitable linker found)
endif

CFLAGS := -ffreestanding -fno-builtin -nostdlib -fPIC
CFLAGS += -target x86_64-sie-ps5 -fno-plt -fno-stack-protector
CFLAGS += -Wall -Werror

all: crt1.o

crt1.o: crt.o klog.o nid.o kernel.o rtld.o patch.o mdbg.o
	$(LD) -m elf_x86_64 -r -o $@ $^

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $^

clean:
	rm -f *.o

install: crt1.o
	install -d $(DESTDIR)/target/lib
	install $^ $(DESTDIR)/target/lib
