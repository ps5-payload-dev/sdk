/*-
 * Copyright (c) 2002 Poul-Henning Kamp
 * Copyright (c) 2002 Networks Associates Technology, Inc.
 * All rights reserved.
 *
 * This software was developed for the FreeBSD Project by Poul-Henning Kamp
 * and NAI Labs, the Security Research Division of Network Associates, Inc.
 * under DARPA/SPAWAR contract N66001-01-C-8035 ("CBOSS"), as part of the
 * DARPA CHATS research program.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The names of the authors may not be used to endorse or promote
 *    products derived from this software without specific prior written
 *    permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $FreeBSD: releng/11.4/sys/sys/kerneldump.h 331722 2018-03-29 02:50:57Z eadler $
 */

#ifndef _SYS_KERNELDUMP_H
#define _SYS_KERNELDUMP_H

#include <machine/endian.h>

#if BYTE_ORDER == LITTLE_ENDIAN
#define	dtoh32(x)	__bswap32(x)
#define	dtoh64(x)	__bswap64(x)
#define	htod32(x)	__bswap32(x)
#define	htod64(x)	__bswap64(x)
#elif BYTE_ORDER == BIG_ENDIAN
#define	dtoh32(x)	(x)
#define	dtoh64(x)	(x)
#define	htod32(x)	(x)
#define	htod64(x)	(x)
#endif

/*
 * All uintX_t fields are in dump byte order, which is the same as
 * network byte order. Use the macros defined above to read or
 * write the fields.
 */
struct kerneldumpheader {
	char		magic[20];
#define	KERNELDUMPMAGIC		"FreeBSD Kernel Dump"
#define	TEXTDUMPMAGIC		"FreeBSD Text Dump"
#define	KERNELDUMPMAGIC_CLEARED	"Cleared Kernel Dump"
	char		architecture[12];
	uint32_t	version;
#define	KERNELDUMPVERSION	1
	uint32_t	architectureversion;
#define	KERNELDUMP_AARCH64_VERSION	1
#define	KERNELDUMP_AMD64_VERSION	2
#define	KERNELDUMP_ARM_VERSION		1
#define	KERNELDUMP_I386_VERSION		2
#define	KERNELDUMP_MIPS_VERSION		1
#define	KERNELDUMP_POWERPC_VERSION	1
#define	KERNELDUMP_RISCV_VERSION	1
#define	KERNELDUMP_SPARC64_VERSION	1
#define	KERNELDUMP_TEXT_VERSION		1
	uint64_t	dumplength;		/* excl headers */
	uint64_t	dumptime;
	uint32_t	blocksize;
	char		hostname[64];
	char		versionstring[192];
	char		panicstring[192];
	uint32_t	parity;
};

/*
 * Parity calculation is endian insensitive.
 */
static __inline u_int32_t
kerneldump_parity(struct kerneldumpheader *kdhp)
{
	uint32_t *up, parity;
	u_int i;

	up = (uint32_t *)kdhp;
	parity = 0;
	for (i = 0; i < sizeof *kdhp; i += sizeof *up)
		parity ^= *up++;
	return (parity);
}

#ifdef _KERNEL
struct dump_pa {
	vm_paddr_t pa_start;
	vm_paddr_t pa_size;
};

void mkdumpheader(struct kerneldumpheader *kdh, char *magic, uint32_t archver,
    uint64_t dumplen, uint32_t blksz);

int dumpsys_generic(struct dumperinfo *);

void dumpsys_map_chunk(vm_paddr_t, size_t, void **);
typedef int dumpsys_callback_t(struct dump_pa *, int, void *);
int dumpsys_foreach_chunk(dumpsys_callback_t, void *);
int dumpsys_cb_dumpdata(struct dump_pa *, int, void *);
int dumpsys_buf_write(struct dumperinfo *, char *, size_t);
int dumpsys_buf_flush(struct dumperinfo *);

void dumpsys_gen_pa_init(void);
struct dump_pa *dumpsys_gen_pa_next(struct dump_pa *);
void dumpsys_gen_wbinv_all(void);
void dumpsys_gen_unmap_chunk(vm_paddr_t, size_t, void *);
int dumpsys_gen_write_aux_headers(struct dumperinfo *);

extern int do_minidump;

#endif

#endif /* _SYS_KERNELDUMP_H */
