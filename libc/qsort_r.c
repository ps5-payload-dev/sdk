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


typedef struct qsort_adapt {
  void *ctx;
  int (*cmp)(void* ctx, const void* x, const void* y);
} qsort_adapt_t;


void qsort_s(void* base, size_t nmemb, size_t size,
	     int (*cmp)(const void *, const void *, void *),
	     void* ctx);


static int
qsort_adapt_cmp(const void *x, const void *y, void *ctx) {
  qsort_adapt_t* adapt = (qsort_adapt_t*)ctx;
  return adapt->cmp(adapt->ctx, x, y);
}


void
qsort_r(void* base, size_t nmemb, size_t size, void* ctx,
	int (*cmp)(void *, const void *, const void *)) {
  qsort_adapt_t qsort_adapt_ctx = {ctx, cmp};
  qsort_s(base, nmemb, size, &qsort_adapt_cmp, &qsort_adapt_ctx);
}
