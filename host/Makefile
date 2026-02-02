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

TOOLCHAINS := toolchain/prospero.sh \
              toolchain/prospero.mk \
              toolchain/prospero.cmake \
              toolchain/prospero.ini

TOOLS := bin/prospero-cmake \
         bin/prospero-llvm \
         bin/prospero-meson \
         bin/prospero-llvm-config \
         bin/prospero-clang \
         bin/prospero-clang++ \
         bin/prospero-deploy \
         bin/prospero-lld \
         bin/prospero-pkg-config \
         bin/prospero-nid \
         bin/prospero-fetchpkg \
         bin/prospero-cross-fix-root

LDSCRIPTS := elf_x86_64.x

.PHONY: all clean install

all: bin/prospero-nid

clean:
	rm -f bin/prospero-nid

bin/prospero-nid: bin/prospero-nid.c
	$(CC) -o $@ $<

install: install-tools install-symlinks install-ldscripts install-toolchains

install-ldscripts: $(LDSCRIPTS)
	install -d $(DESTDIR)/ldscripts
	install $^ $(DESTDIR)/ldscripts
	install -d $(DESTDIR)/target/lib
	ln -sf ../../ldscripts/elf_x86_64.x $(DESTDIR)/target/lib/main.script
	ln -sf ../../ldscripts/elf_x86_64.x $(DESTDIR)/target/lib/prx.script

install-toolchains: $(TOOLCHAINS)
	install -d $(DESTDIR)/toolchain
	install $^ $(DESTDIR)/toolchain

install-tools: $(TOOLS)
	install -d $(DESTDIR)/bin
	install $^ $(DESTDIR)/bin

install-symlinks:
	ln -sf prospero-llvm $(DESTDIR)/bin/llvm-ar
	ln -sf prospero-llvm $(DESTDIR)/bin/llvm-nm
	ln -sf prospero-llvm $(DESTDIR)/bin/llvm-objcopy
	ln -sf prospero-llvm $(DESTDIR)/bin/llvm-ranlib
	ln -sf prospero-llvm $(DESTDIR)/bin/llvm-strip
	ln -sf prospero-llvm $(DESTDIR)/bin/clang
	ln -sf prospero-llvm $(DESTDIR)/bin/clang++
	ln -sf prospero-llvm $(DESTDIR)/bin/clang-cpp
	ln -sf prospero-llvm $(DESTDIR)/bin/ld.lld
	ln -sf llvm-ar $(DESTDIR)/bin/prospero-ar
	ln -sf llvm-nm $(DESTDIR)/bin/prospero-nm
	ln -sf llvm-objcopy $(DESTDIR)/bin/prospero-objcopy
	ln -sf llvm-ranlib $(DESTDIR)/bin/prospero-ranlib
	ln -sf llvm-strip $(DESTDIR)/bin/prospero-strip
	ln -sf prospero-clang $(DESTDIR)/bin/prospero-as
