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

#include <stdlib.h>


void qsort_s(void *base, size_t nmemb, size_t size,
	     int (*cmp)(void *, const void *, const void *), void* arg);


/**
 * Note, the order of the last two args is different from GNU and C11.
 * This was fixed in FreeBSD 14.
 **/
void
qsort_r(void *base, size_t nmemb, size_t size, void *arg,
	int (*cmp)(void *, const void *, const void *)) {
  qsort_s(base, nmemb, size, cmp, arg);
}
