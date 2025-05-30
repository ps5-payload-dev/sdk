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

PHDRS {
	ph_text   PT_LOAD FLAGS (0x7);
	ph_rodata PT_LOAD FLAGS (0x6);
	ph_data   PT_LOAD FLAGS (0x6);
	ph_dyn    PT_DYNAMIC;
}

SECTIONS {
	PROVIDE_HIDDEN (__image_start = .);

	.text : ALIGN(CONSTANT(MAXPAGESIZE)) {
	    PROVIDE_HIDDEN (__text_start = .);
	    *(.text .text.*)
	    PROVIDE_HIDDEN (__text_end = .);
	} : ph_text

	.plt : { *(.plt) }

	.eh_frame_hdr : ALIGN(CONSTANT(MAXPAGESIZE)) {
	    PROVIDE_HIDDEN(__eh_frame_hdr_start = .);
	    KEEP(*(.eh_frame_hdr))
	    PROVIDE_HIDDEN(__eh_frame_hdr_end = .);
	} : ph_rodata

	.eh_frame : {
	    PROVIDE_HIDDEN(__eh_frame_start = .);
	    KEEP(*(.eh_frame))
	    PROVIDE_HIDDEN(__eh_frame_end = .);
	}

	.gcc_except_table : { *(.gcc_except_table*) }
	.data.rel.ro : { *(.data.rel.ro .data.rel.ro.*); }
	.got : { *(.got) }
	.got.plt : { *(.got.plt) }

	.rodata : { *(.rodata .rodata.*) }

	.preinit_array : {
	    PROVIDE_HIDDEN(__preinit_array_start = .);
	    KEEP(*(.preinit_array))
	    PROVIDE_HIDDEN(__preinit_array_start = .);
	}
	.init_array : {
	    PROVIDE_HIDDEN(__init_array_start = .);
	    KEEP(*(SORT_BY_INIT_PRIORITY(.init_array.*) SORT_BY_INIT_PRIORITY(.ctors.*)))
	    KEEP(*(.init_array .ctors))
	    PROVIDE_HIDDEN(__init_array_end = .);
	}
	.fini_array : {
	    PROVIDE_HIDDEN(__fini_array_start = .);
	    KEEP(*(SORT_BY_INIT_PRIORITY(.fini_array.*) SORT_BY_INIT_PRIORITY(.dtors.*)))
	    KEEP(*(.fini_array .dtors))
	    PROVIDE_HIDDEN(__fini_array_end = .);
	}

	.dynamic : ALIGN(CONSTANT(MAXPAGESIZE)) {
	    PROVIDE_HIDDEN (_DYNAMIC = .);
	    *(.dynamic)
	} : ph_rodata : ph_dyn

	.data : ALIGN(CONSTANT(MAXPAGESIZE)) {
	    *(.data .data.*)
	} : ph_data

	.bss : {
	    PROVIDE_HIDDEN (__bss_start = .);
	    *(.bss .bss.*);
	    *(COMMON)
	    PROVIDE_HIDDEN (__bss_end = .);
	}

	PROVIDE_HIDDEN (__image_end = .);
}
