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

include ../common.mk

CFLAGS := -ffreestanding -fno-builtin -nostdlib -fPIC
CFLAGS += -target x86_64-sie-ps5 -fno-plt -fno-stack-protector
CFLAGS += -Wall -Werror -fvisibility-nodllstorageclass=default

SPRXS := $(wildcard *.sprx)
STUBS := $(SPRXS:.sprx=.c)

SOURCES  := $(wildcard *.c)
SHARED   := $(SOURCES:.c=.so)

NID_DB     := aerolib.csv
NID_DB_URL := https://raw.githubusercontent.com/zecoxao/sce_symbols/main/$(NID_DB)

.PHONY: all clean install

all: $(SOURCES) $(SHARED)

stubs: $(NID_DB) $(STUBS)

$(NID_DB):
	wget -O $@ $(NID_DB_URL)

%.c: %.sprx
	$(PYTHON) genstub.py $^ > $@

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $^

# TODO: fix DT_NEEDED deps
libSceAppInstUtil.so: libSceIpmi.so

%.so: %.o
	$(LD) -m elf_x86_64 -shared -soname $*.sprx -o $@ $<

clean:
	rm -f *.o *.so $(NID_DB)

install: $(SHARED)
	install -d $(DESTDIR)/target/lib
	install $(SHARED) $(DESTDIR)/target/lib
	ln -sf libkernel_web.so $(DESTDIR)/target/lib/libkernel_stub_weak.so
	ln -sf libSceLibcInternal.so $(DESTDIR)/target/lib/libc_stub_weak.so
