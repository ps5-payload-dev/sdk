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

set(PS5_PAYLOAD_SDK "${CMAKE_CURRENT_LIST_DIR}/.." CACHE PATH "")
set(PS5 TRUE)
set(PROSPERO TRUE)

#
# The PS5 is running a modified FreeBSD kernel on a x86_64 CPU
#
set(CMAKE_SYSTEM_PROCESSOR x86_64)
set(CMAKE_SYSTEM_NAME FreeBSD)
set(CMAKE_SYSTEM_VERSION 9)
set(CMAKE_CROSSCOMPILING 1)

#
# Set sysroot and search paths
#
set(CMAKE_SYSROOT "${PS5_PAYLOAD_SDK}/target")
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM BOTH)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

#
# Set prefix (on the target platform)
#
set(CMAKE_INSTALL_PREFIX "/user/homebrew" CACHE PATH "")

#
# Encrease default verbosity in makefiles
#
set(CMAKE_VERBOSE_MAKEFILE ON CACHE BOOL "")

#
# We only support positional independent executables
#
set(BUILD_SHARED_LIBS OFF CACHE INTERNAL "Shared libs turned off by default")
set(CMAKE_POSITION_INDEPENDENT_CODE ON CACHE BOOL "")

#
# Set external tool dependencies
#
if(WIN32)
    set(CMAKE_ASM_COMPILER ${PS5_PAYLOAD_SDK}/win/prospero-clang.cmd CACHE PATH "")
    set(CMAKE_C_COMPILER ${PS5_PAYLOAD_SDK}/win/prospero-clang.cmd CACHE PATH "")
    set(CMAKE_CXX_COMPILER ${PS5_PAYLOAD_SDK}/win/prospero-clang++.cmd CACHE PATH "")
    set(CMAKE_LINKER ${PS5_PAYLOAD_SDK}/bin/prospero-lld.exe CACHE PATH "")
else()
    set(CMAKE_ASM_COMPILER ${PS5_PAYLOAD_SDK}/bin/prospero-as CACHE PATH "")
    set(CMAKE_C_COMPILER ${PS5_PAYLOAD_SDK}/bin/prospero-clang CACHE PATH "")
    set(CMAKE_CXX_COMPILER ${PS5_PAYLOAD_SDK}/bin/prospero-clang++ CACHE PATH "")
    set(CMAKE_LINKER ${PS5_PAYLOAD_SDK}/bin/prospero-lld CACHE PATH "")

    set(CMAKE_AR ${PS5_PAYLOAD_SDK}/bin/prospero-ar CACHE PATH "")
    set(CMAKE_C_COMPILER_AR ${PS5_PAYLOAD_SDK}/bin/prospero-ar CACHE PATH "")
    set(CMAKE_CXX_COMPILER_AR ${PS5_PAYLOAD_SDK}/bin/prospero-ar CACHE PATH "")

    set(CMAKE_RANLIB ${PS5_PAYLOAD_SDK}/bin/prospero-ranlib CACHE PATH "")
    set(CMAKE_C_COMPILER_RANLIB ${PS5_PAYLOAD_SDK}/bin/prospero-ranlib CACHE PATH "")
    set(CMAKE_CXX_COMPILER_RANLIB ${PS5_PAYLOAD_SDK}/bin/prospero-ranlib CACHE PATH "")

    set(CMAKE_STRIP ${PS5_PAYLOAD_SDK}/bin/prospero-strip CACHE PATH "")

    set(PKG_CONFIG_EXECUTABLE ${PS5_PAYLOAD_SDK}/bin/prospero-pkg-config CACHE PATH "")
    set(CMAKE_FIND_PACKAGE_PREFER_CONFIG TRUE)
endif()
