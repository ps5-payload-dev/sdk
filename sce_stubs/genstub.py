#!/usr/bin/env python3
# encoding: utf-8
# Copyright (C) 2023 John Törnblom
#
# This program is free software; you can redistribute it and/or modify it
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

import argparse
import logging
import os
import string
import sys

from pathlib import Path
from elftools.elf.elffile import ELFFile


logger = logging.getLogger('genstub')


tmpl_func = string.Template('''
asm(".global $name\\n"
    ".type $name @function\\n"
    "$name:\\n");''')


tmpl_obj = string.Template('''
asm(".global $name\\n"
    ".type   $name, @object\\n"
    "$name:\\n");''')


# read NIDs from aerolib.csv
NID_DB = (os.path.dirname(__file__) or '.') + '/aerolib.csv'
nid_map = {}
with open(NID_DB) as f:
    for line in f.readlines():
        nid, sym = line.strip().split(' ', 1)
        nid_map[nid] = sym


def symbols(sym_type, filename):
    '''
    yield symbol names in PT_DYNAMIC segments using the NID lookup table
    'nid_db.xml'.
    '''
    with open(filename, 'rb') as f:
        elf = ELFFile(f)

        for segment in elf.iter_segments():
            if segment.header.p_type != 'PT_DYNAMIC':
                continue

            for sym in segment.iter_symbols():
                if sym_type != sym.entry['st_info']['type']:
                    continue

                if sym.entry['st_shndx'] == 'SHN_UNDEF':
                    continue

                if not sym.name:
                    continue

                nid, lid, mid = sym.name.split('#')
                if not nid in nid_map:
                    logger.warning(f'skipping unknown NID {nid}')
                    continue

                yield nid_map[nid]


if __name__ == '__main__':
    logging.basicConfig(level=logging.WARNING)

    parser = argparse.ArgumentParser()
    parser.add_argument('SPRX_FILE')
    cli_args = parser.parse_args()

    funcs = sorted(set(symbols('STT_FUNC', cli_args.SPRX_FILE)))
    gvars = sorted(set(symbols('STT_OBJECT', cli_args.SPRX_FILE)))

    for name in sorted(funcs):
        print(tmpl_func.substitute(name=name))

    for name in sorted(gvars):
        print(tmpl_obj.substitute(name=name))

