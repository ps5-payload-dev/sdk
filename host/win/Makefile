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

TOOLS := prospero-lld.exe prospero-clang.cmd prospero-clang++.cmd

all: prospero-lld.exe

prospero-lld.exe: prospero-lld.c
	$(CC) -o $@ $^

clean:
	rm -f *.exe *.o

install: $(TOOLS)
	install -d $(DESTDIR)/win
	install $^ $(DESTDIR)/win
