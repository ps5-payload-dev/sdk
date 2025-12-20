#!/usr/bin/env bash
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

SCRIPTDIR="${BASH_SOURCE[0]}"
SCRIPTDIR="$(dirname "${SCRIPTDIR}")"

export DESTDIR=$(mktemp -d)
trap 'rm -rf -- "$DESTDIR"' EXIT

make clean install || exit 1
export PS5_PAYLOAD_SDK=$DESTDIR
$SCRIPTDIR/libcxx.sh || exit 1

MAKE_SAMPLES=("arbitrary_syscall"
	      "browser"
	      "hello_cxx"
	      "hello_cxx23"
	      "hello_dlfcn"
	      "hello_kenv"
	      "hello_sprx"
	      "hello_stdio"
	      "hello_world"
	      "hwinfo"
	      "install_app"
	      "list_files"
	      "mntinfo"
	      "notify"
	      "notify_debug"
	      "ps")

CMAKE_SAMPLES=("hello_cmake"
	      )

MESON_SAMPLES=("hello_meson"
	      )

source $PS5_PAYLOAD_SDK/toolchain/prospero.sh

for SAMPLE in "${MAKE_SAMPLES[@]}"; do
    ${MAKE} -C $PS5_PAYLOAD_SDK/samples/$SAMPLE clean all || exit 1
done

for SAMPLE in "${CMAKE_SAMPLES[@]}"; do
    ${CMAKE} \
	-DCMAKE_VERBOSE_MAKEFILE=YES \
	-B $PS5_PAYLOAD_SDK/build/$SAMPLE \
	-S $SCRIPTDIR/samples/$SAMPLE || exit 1
    ${CMAKE} --build $PS5_PAYLOAD_SDK/build/$SAMPLE
done

for SAMPLE in "${MESON_SAMPLES[@]}"; do
    ${MESON} setup \
	     $SCRIPTDIR/samples/$SAMPLE \
	     $PS5_PAYLOAD_SDK/build/$SAMPLE
    ${MESON} compile -C $PS5_PAYLOAD_SDK/build/$SAMPLE
done
