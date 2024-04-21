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

MAKE    ?= make
DESTDIR ?= /opt/ps5-payload-sdk

TOPTARGETS := all clean install
SUBDIRS    := crt sce_stubs host

$(TOPTARGETS): $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)

.PHONY: $(TOPTARGETS) $(SUBDIRS)

install: elf_x86_64.x toolchain.cmake toolchain.mk toolchain.sh
	install -d $(DESTDIR)/ldscripts
	install elf_x86_64.x $(DESTDIR)/ldscripts

	install -d $(DESTDIR)/cmake
	install toolchain.cmake $(DESTDIR)/cmake

	install -d $(DESTDIR)/make
	install toolchain.mk $(DESTDIR)/make

	install -d $(DESTDIR)/shell
	install toolchain.sh $(DESTDIR)/shell

	cp -r include_bsd/. $(DESTDIR)/sysroot/usr/include
	cp -r include_ps5/. $(DESTDIR)/sysroot/usr/include/ps5
	cp -r include_khronos/. $(DESTDIR)/sysroot/usr/include

	cp -r samples/. $(DESTDIR)/samples
