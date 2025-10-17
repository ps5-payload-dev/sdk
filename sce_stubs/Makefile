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

PYTHON  ?= python3
DESTDIR ?= /opt/ps5-payload-sdk

LLVM_CONFIG_CANDIDATES := llvm-config-20 llvm-config-19 llvm-config-18 \
                          llvm-config-17 llvm-config-16 llvm-config-15 \
                          llvm-config
LLVM_CONFIG_CANDIDATES := $(foreach LCC,$(LLVM_CONFIG_CANDIDATES), \
                          $(if $(shell command -v $(LCC) 2>/dev/null), $(LCC)))

LLVM_CONFIG ?= $(firstword $(LLVM_CONFIG_CANDIDATES))
ifndef LLVM_CONFIG
    $(error Unable to find llvm-config)
endif

LLVM_BINDIR := $(shell $(LLVM_CONFIG) --bindir)
CC := $(LLVM_BINDIR)/clang
LD := $(LLVM_BINDIR)/ld.lld

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

libdl.so: libkernel_web.o
	$(LD) -m elf_x86_64 -shared -soname libkernel_web.sprx -o $@ $<

libpthread.so: libkernel_web.o
	$(LD) -m elf_x86_64 -shared -soname libkernel_web.sprx -o $@ $<

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
