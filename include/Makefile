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

all:

clean:

install:
	install -d $(DESTDIR)/target/include
	cp -r freebsd/. $(DESTDIR)/target/include
	cp -r khronos/. $(DESTDIR)/target/include
	cp -r ps5/. $(DESTDIR)/target/include/ps5

	install -d $(DESTDIR)/target/user/homebrew/include
	ln -sf user/homebrew/include $(DESTDIR)/target/include_common
