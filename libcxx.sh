#!/usr/bin/env bash
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

LLVM_URL="https://github.com/llvm/llvm-project/releases/download"
LLVM_VER="18.1.8"

if [[ -z "$PS5_PAYLOAD_SDK" ]]; then
    echo "error: PS5_PAYLOAD_SDK is not set"
    exit 1
fi

source ${PS5_PAYLOAD_SDK}/toolchain/prospero.sh || exit 1

TEMPDIR=$(mktemp -d)
trap 'rm -rf -- "$TEMPDIR"' EXIT

wget -O $TEMPDIR/llvm.tar.xz \
     $LLVM_URL/llvmorg-$LLVM_VER/llvm-project-$LLVM_VER.src.tar.xz || exit 1
tar xf $TEMPDIR/llvm.tar.xz -C $TEMPDIR || exit 1

${CMAKE} -S $TEMPDIR/llvm-project-$LLVM_VER.src/runtimes \
	 -B $TEMPDIR/build \
	 -DCMAKE_INSTALL_PREFIX="${PS5_SYSROOT}" \
	 -DCMAKE_BUILD_TYPE=Release \
	 -DCMAKE_CXX_FLAGS="-nostdlib++" \
	 -DLLVM_ENABLE_RUNTIMES="libunwind;libcxxabi;libcxx" \
	 -DLIBCXX_ENABLE_STATIC=YES \
	 -DLIBCXX_ENABLE_RTTI=YES \
	 -DLIBCXX_ENABLE_EXCEPTIONS=YES \
	 -DLIBCXX_ENABLE_THREADS=YES \
	 -DLIBCXX_ENABLE_SHARED=NO \
	 -DLIBCXX_ENABLE_ABI_LINKER_SCRIPT=NO \
	 -DLIBCXX_CXX_ABI=libcxxabi \
	 -DLIBCXXABI_ENABLE_STATIC=YES \
	 -DLIBCXXABI_ENABLE_EXCEPTIONS=YES \
	 -DLIBCXXABI_ENABLE_THREADS=YES \
	 -DLIBCXXABI_USE_LLVM_UNWINDER=YES \
	 -DLIBCXXABI_ENABLE_SHARED=NO \
	 -DLIBCXXABI_USE_COMPILER_RT=NO \
	 -DLIBUNWIND_ENABLE_STATIC=YES \
	 -DLIBUNWIND_ENABLE_THREADS=YES \
	 -DLIBUNWIND_IS_BAREMETAL=YES \
	 -DLIBUNWIND_ENABLE_SHARED=NO \
	 -DLIBUNWIND_USE_COMPILER_RT=NO || exit 1
${MAKE} -C $TEMPDIR/build install DESTDIR="/"
