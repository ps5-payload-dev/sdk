/*-
 * Copyright (c) 2005 John Baldwin <jhb@FreeBSD.org>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
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
 * $FreeBSD: releng/11.1/sys/sys/refcount.h 261520 2014-02-05 18:13:27Z jhb $
 */

#ifndef __SYS_REFCOUNT_H__
#define __SYS_REFCOUNT_H__

#include <sys/limits.h>
#include <machine/atomic.h>

#ifdef _KERNEL
#include <sys/systm.h>
#else
#define	KASSERT(exp, msg)	/* */
#endif

static __inline void
refcount_init(volatile u_int *count, u_int value)
{

	*count = value;
}

static __inline void
refcount_acquire(volatile u_int *count)
{

	KASSERT(*count < UINT_MAX, ("refcount %p overflowed", count));
	atomic_add_acq_int(count, 1);	
}

static __inline int
refcount_release(volatile u_int *count)
{
	u_int old;

	/* XXX: Should this have a rel membar? */
	old = atomic_fetchadd_int(count, -1);
	KASSERT(old > 0, ("negative refcount %p", count));
	return (old == 1);
}

#endif	/* ! __SYS_REFCOUNT_H__ */
