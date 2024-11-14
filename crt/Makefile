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

ARS := llvm-ar-18 llvm-ar-17 llvm-ar-16 llvm-ar-15 llvm-ar ar
ARS := $(foreach AR,$(ARS),$(if $(shell command -v $(AR) 2> /dev/null),$(AR)))
AR  := $(firstword $(ARS))
ifndef AR
    $(error No suitable archiver found)
endif

CFLAGS += -ffreestanding -fno-builtin -nostdlib -fPIC
CFLAGS += -target x86_64-sie-ps5 -fno-plt -fno-stack-protector
CFLAGS += -fvisibility-nodllstorageclass=default -Wall -Werror
CFLAGS += -fms-extensions -Wno-microsoft-anon-tag
CFLAGS += -g

OBJ := crt.o syscall.o klog.o nid.o kernel.o rtld.o rtld_so.o rtld_sprx.o \
       rtld_payload.o patch.o mdbg.o

ARCHIVE := libcrt.a

all: $(ARCHIVE)

$(ARCHIVE): $(OBJ)
	$(AR) -rsc $@ $^

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $^

clean:
	rm -f *.o *.a

install: $(ARCHIVE)
	install -d $(DESTDIR)/target/lib
	install $^ $(DESTDIR)/target/lib
