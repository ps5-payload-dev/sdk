/* Copyright (C) 2024 John Törnblom

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
ENTRY(_start)

PHDRS {
	ph_text   PT_LOAD FLAGS (0x5);
	ph_rodata PT_LOAD FLAGS (0x4);
	ph_data   PT_LOAD FLAGS (0x6);
	ph_dyn    PT_DYNAMIC;
}

SECTIONS {
	.text : ALIGN(CONSTANT(MAXPAGESIZE)) {
	    PROVIDE_HIDDEN (__text_start = .);
	    *(.text .text.*)
	    PROVIDE_HIDDEN (__text_end = .);
	} : ph_text

	.rodata : ALIGN(CONSTANT(MAXPAGESIZE)) {
	    *(.rodata .rodata.*)

	    PROVIDE_HIDDEN(__init_array_start = .);
	    KEEP(*(SORT_BY_INIT_PRIORITY(.init_array.*) SORT_BY_INIT_PRIORITY(.ctors.*)))
	    KEEP(*(.init_array .ctors))
	    PROVIDE_HIDDEN(__init_array_end = .);

	    PROVIDE_HIDDEN(__fini_array_start = .);
	    KEEP(*(SORT_BY_INIT_PRIORITY(.fini_array.*) SORT_BY_INIT_PRIORITY(.dtors.*)))
	    KEEP(*(.fini_array .dtors))
	    PROVIDE_HIDDEN(__fini_array_end = .);
	} : ph_rodata

	.rela : { *(.rela *.rela.*) }

	.data : ALIGN(CONSTANT(MAXPAGESIZE)) {
	    *(.data .data.*)
	} : ph_data

	.dynamic : ALIGN(CONSTANT(MAXPAGESIZE)) {
	    PROVIDE_HIDDEN (_DYNAMIC = .);
	    *(.dynamic)
	} : ph_data : ph_dyn

	.bss (NOLOAD) : ALIGN(CONSTANT(MAXPAGESIZE)) {
	    PROVIDE_HIDDEN (__bss_start = .);
	    *(.bss .bss.*);
	    *(COMMON)
	    PROVIDE_HIDDEN (__bss_end = .);
	} : ph_data
}
