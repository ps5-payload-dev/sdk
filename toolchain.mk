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

PS5_PAYLOAD_SDK := $(abspath $(dir $(lastword $(MAKEFILE_LIST)))..)
PS5_SYSROOT     := $(PS5_PAYLOAD_SDK)/sysroot
PS5_DEPLOY      := $(PS5_PAYLOAD_SDK)/bin/prospero-deploy

CC  := $(PS5_PAYLOAD_SDK)/bin/prospero-clang
CXX := $(PS5_PAYLOAD_SDK)/bin/prospero-clang++
AS  := $(PS5_PAYLOAD_SDK)/bin/prospero-clang
LD  := $(PS5_PAYLOAD_SDK)/bin/prospero-lld

AR      := llvm-ar
NM      := llvm-nm
OBJCOPY := llvm-objcopy
RANLIB  := llvm-ranlib
STRIP   := llvm-strip
STRINGS := strings

PKG_CONFIG := $(PS5_PAYLOAD_SDK)/bin/prospero-pkg-config
