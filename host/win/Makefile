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

CC := x86_64-w64-mingw32-gcc
NINJA := https://github.com/ninja-build/ninja/releases/download/v1.12.1/ninja-win.zip

TOOLS := prospero-lld.exe ninja.exe \
         prospero-clang.cmd prospero-clang++.cmd prospero-cmake.cmd

all: prospero-lld.exe ninja.exe

prospero-lld.exe: prospero-lld.c
	$(CC) -o $@ $^

ninja.exe:
	wget -q -O - $(NINJA) | gunzip -c -d > $@

clean:
	rm -f *.exe *.o

install: $(TOOLS)
	install -d $(DESTDIR)/win
	install $^ $(DESTDIR)/win
