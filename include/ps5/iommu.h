/* Copyright (C) 2026 John Törnblom

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

#pragma once

#include <sys/cdefs.h>
#include <stdint.h>


__BEGIN_DECLS


/**
 * Copy data into the kernel via iommu write commands, thus bypassing some of
 * the write permission checks when going via the CPU.
 **/
int kernel_iommu_copyin(const void *buf, intptr_t kaddr, size_t len);


/**
 * Convenience functions for common uses of kernel_iommu_copyin().
 **/
int kernel_iommu_setchar(intptr_t kaddr, char val);
int kernel_iommu_setshort(intptr_t kaddr, short val);
int kernel_iommu_setint(intptr_t kaddr, int val);
int kernel_iommu_setlong(intptr_t kaddr, long val);


__END_DECLS
