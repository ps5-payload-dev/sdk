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

TOOLS := bin/cmake-bin-wrapper \
         bin/llvm-bin-wrapper \
         bin/llvm-config \
         bin/prospero-clang \
         bin/prospero-clang++ \
         bin/prospero-deploy \
         bin/prospero-lld \
         bin/prospero-pkg-config \
         bin/prospero-nid \
         bin/prospero-fetchpkg \
         bin/prospero-cross-fix-root

LDSCRIPTS := elf_x86_64.x

all: bin/prospero-nid

clean:
	rm -f bin/prospero-nid

bin/prospero-nid: bin/prospero-nid.c
	$(CC) -static -o $@ $<

install: install-tools install-symlinks install-ldscripts install-toolchains

install-ldscripts: $(LDSCRIPTS)
	install -d $(DESTDIR)/ldscripts
	install $^ $(DESTDIR)/ldscripts

install-toolchains: $(TOOLCHAINS)
	install -d $(DESTDIR)/toolchain
	install $^ $(DESTDIR)/toolchain

install-tools: $(TOOLS)
	install -d $(DESTDIR)/bin
	install $^ $(DESTDIR)/bin

install-symlinks:
	ln -sf llvm-bin-wrapper $(DESTDIR)/bin/llvm-ar
	ln -sf llvm-bin-wrapper $(DESTDIR)/bin/llvm-nm
	ln -sf llvm-bin-wrapper $(DESTDIR)/bin/llvm-objcopy
	ln -sf llvm-bin-wrapper $(DESTDIR)/bin/llvm-ranlib
	ln -sf llvm-bin-wrapper $(DESTDIR)/bin/llvm-strip
	ln -sf llvm-bin-wrapper $(DESTDIR)/bin/clang
	ln -sf llvm-bin-wrapper $(DESTDIR)/bin/clang++
	ln -sf llvm-bin-wrapper $(DESTDIR)/bin/clang-cpp
	ln -sf llvm-bin-wrapper $(DESTDIR)/bin/ld.lld
	ln -sf cmake-bin-wrapper $(DESTDIR)/bin/prospero-cmake
