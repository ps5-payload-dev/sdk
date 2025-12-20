/* Copyright (C) 2025 John Törnblom

This program is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 3, or (at your option) any
later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; see the file COPYING. If not, see
<http://www.gnu.org/licenses/>.  */

OUTPUT_FORMAT("elf64-x86-64")
OUTPUT_ARCH(i386:x86-64)

PHDRS {
	ph_text          PT_LOAD    FLAGS(0x1);
	ph_rodata        PT_LOAD    FLAGS(0x4);
	ph_data          PT_LOAD    FLAGS(0x6);
	ph_sce_procparam 0x61000001 FLAGS(0x4);
}

SECTIONS {
	. = CONSTANT(MAXPAGESIZE);

	.text : ALIGN(CONSTANT(MAXPAGESIZE)) {
	    __text_start__ = .;
	    *(.text .text.*)
	    __text_end__ = .;
	} : ph_text

	.rodata : ALIGN(CONSTANT(MAXPAGESIZE)) {
	    __rodata_start__ = .;
	    *(.rodata .rodata.*)
	    __rodata_end__ = .;
	}: ph_rodata

	.data : ALIGN(CONSTANT(MAXPAGESIZE)) {
	    __data_start__ = .;
	    *(.data .data.*)
	    __data_end__ = .;
	} : ph_data

	.sce_process_param : ALIGN(32) {
	    KEEP(*(.sce_process_param))
	} : ph_sce_procparam
}
