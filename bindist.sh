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

SCRIPTDIR="${BASH_SOURCE[0]}"
SCRIPTDIR="$(dirname "${SCRIPTDIR}")"

DISTDIR="${PWD}"
VER=$(git describe --abbrev=10 --dirty --always --tags)

export TEMPDIR=$(mktemp -d)
trap 'rm -rf -- "$TEMPDIR"' EXIT

export DESTDIR="${TEMPDIR}/ps5-payload-sdk-${VER}"
export PS5_PAYLOAD_SDK=$DESTDIR
export WIN=1 # also build windows tools

make clean install || exit 1
"${SCRIPTDIR}/libcxx.sh" || exit 1

cd "${TEMPDIR}"
zip -r "${DISTDIR}/ps5-payload-sdk-${VER}.zip" "ps5-payload-sdk-${VER}"
