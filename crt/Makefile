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
AR := $(LLVM_BINDIR)/llvm-ar
LD := $(LLVM_BINDIR)/ld.lld

CFLAGS += -ffreestanding -fno-builtin -nostdlib -fPIC
CFLAGS += -target x86_64-sie-ps5 -fno-plt -fno-stack-protector
CFLAGS += -fvisibility-nodllstorageclass=default -Wall -Werror
CFLAGS += -fms-extensions -Wno-microsoft-anon-tag
CFLAGS += -O1

OBJ := crt.o syscall.o klog.o nid.o kernel.o rtld.o rtld_so.o rtld_sprx.o \
       rtld_payload.o rtld_dlfcn.o mdbg.o patch.o

.PHONY: all clean install

all: crt1.o crti.o crtn.o crtbegin.o crtend.o crtbeginS.o crtendS.o

crtbeginS.o:
	$(AR) -rsc $@

crtendS.o:
	$(AR) -rsc $@

crtbegin.o:
	$(AR) -rsc $@

crtend.o:
	$(AR) -rsc $@

crti.o:
	$(AR) -rsc $@

crtn.o:
	$(AR) -rsc $@

crt1.o: $(OBJ)
	$(LD) -m elf_x86_64 -r -o $@ $^

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $^

clean:
	rm -f *.o *.a

install: crt1.o crti.o crtn.o crtbegin.o crtend.o crtbeginS.o crtendS.o
	install -d $(DESTDIR)/target/lib
	install $^ $(DESTDIR)/target/lib
