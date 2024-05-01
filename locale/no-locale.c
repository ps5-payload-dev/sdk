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

#include <ctype.h>
#include <locale.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <wchar.h>
#include <wctype.h>


const _RuneLocale _DefaultRuneLocale = {
  _RUNE_MAGIC_1,
  "NONE",
  NULL,
  NULL,
  0xFFFD,
  {_CTYPE_C,
   _CTYPE_C,
   _CTYPE_C,
   _CTYPE_C,
   _CTYPE_C,
   _CTYPE_C,
   _CTYPE_C,
   _CTYPE_C,
   _CTYPE_C,
   _CTYPE_C|_CTYPE_S|_CTYPE_B,
   _CTYPE_C|_CTYPE_S,
   _CTYPE_C|_CTYPE_S,
   _CTYPE_C|_CTYPE_S,
   _CTYPE_C|_CTYPE_S,
   _CTYPE_C,
   _CTYPE_C,
   _CTYPE_C,
   _CTYPE_C,
   _CTYPE_C,
   _CTYPE_C,
   _CTYPE_C,
   _CTYPE_C,
   _CTYPE_C,
   _CTYPE_C,
   _CTYPE_C,
   _CTYPE_C,
   _CTYPE_C,
   _CTYPE_C,
   _CTYPE_C,
   _CTYPE_C,
   _CTYPE_C,
   _CTYPE_C,
   _CTYPE_S|_CTYPE_B|_CTYPE_R,
   _CTYPE_P|_CTYPE_R|_CTYPE_G,
   _CTYPE_P|_CTYPE_R|_CTYPE_G,
   _CTYPE_P|_CTYPE_R|_CTYPE_G,
   _CTYPE_P|_CTYPE_R|_CTYPE_G,
   _CTYPE_P|_CTYPE_R|_CTYPE_G,
   _CTYPE_P|_CTYPE_R|_CTYPE_G,
   _CTYPE_P|_CTYPE_R|_CTYPE_G,
   _CTYPE_P|_CTYPE_R|_CTYPE_G,
   _CTYPE_P|_CTYPE_R|_CTYPE_G,
   _CTYPE_P|_CTYPE_R|_CTYPE_G,
   _CTYPE_P|_CTYPE_R|_CTYPE_G,
   _CTYPE_P|_CTYPE_R|_CTYPE_G,
   _CTYPE_P|_CTYPE_R|_CTYPE_G,
   _CTYPE_P|_CTYPE_R|_CTYPE_G,
   _CTYPE_P|_CTYPE_R|_CTYPE_G,
   _CTYPE_D|_CTYPE_R|_CTYPE_G|_CTYPE_X|_CTYPE_N|0,
   _CTYPE_D|_CTYPE_R|_CTYPE_G|_CTYPE_X|_CTYPE_N|1,
   _CTYPE_D|_CTYPE_R|_CTYPE_G|_CTYPE_X|_CTYPE_N|2,
   _CTYPE_D|_CTYPE_R|_CTYPE_G|_CTYPE_X|_CTYPE_N|3,
   _CTYPE_D|_CTYPE_R|_CTYPE_G|_CTYPE_X|_CTYPE_N|4,
   _CTYPE_D|_CTYPE_R|_CTYPE_G|_CTYPE_X|_CTYPE_N|5,
   _CTYPE_D|_CTYPE_R|_CTYPE_G|_CTYPE_X|_CTYPE_N|6,
   _CTYPE_D|_CTYPE_R|_CTYPE_G|_CTYPE_X|_CTYPE_N|7,
   _CTYPE_D|_CTYPE_R|_CTYPE_G|_CTYPE_X|_CTYPE_N|8,
   _CTYPE_D|_CTYPE_R|_CTYPE_G|_CTYPE_X|_CTYPE_N|9,
   _CTYPE_P|_CTYPE_R|_CTYPE_G,
   _CTYPE_P|_CTYPE_R|_CTYPE_G,
   _CTYPE_P|_CTYPE_R|_CTYPE_G,
   _CTYPE_P|_CTYPE_R|_CTYPE_G,
   _CTYPE_P|_CTYPE_R|_CTYPE_G,
   _CTYPE_P|_CTYPE_R|_CTYPE_G,
   _CTYPE_P|_CTYPE_R|_CTYPE_G,
   _CTYPE_U|_CTYPE_X|_CTYPE_R|_CTYPE_G|_CTYPE_A|10,
   _CTYPE_U|_CTYPE_X|_CTYPE_R|_CTYPE_G|_CTYPE_A|11,
   _CTYPE_U|_CTYPE_X|_CTYPE_R|_CTYPE_G|_CTYPE_A|12,
   _CTYPE_U|_CTYPE_X|_CTYPE_R|_CTYPE_G|_CTYPE_A|13,
   _CTYPE_U|_CTYPE_X|_CTYPE_R|_CTYPE_G|_CTYPE_A|14,
   _CTYPE_U|_CTYPE_X|_CTYPE_R|_CTYPE_G|_CTYPE_A|15,
   _CTYPE_U|_CTYPE_R|_CTYPE_G|_CTYPE_A,
   _CTYPE_U|_CTYPE_R|_CTYPE_G|_CTYPE_A,
   _CTYPE_U|_CTYPE_R|_CTYPE_G|_CTYPE_A,
   _CTYPE_U|_CTYPE_R|_CTYPE_G|_CTYPE_A,
   _CTYPE_U|_CTYPE_R|_CTYPE_G|_CTYPE_A,
   _CTYPE_U|_CTYPE_R|_CTYPE_G|_CTYPE_A,
   _CTYPE_U|_CTYPE_R|_CTYPE_G|_CTYPE_A,
   _CTYPE_U|_CTYPE_R|_CTYPE_G|_CTYPE_A,
   _CTYPE_U|_CTYPE_R|_CTYPE_G|_CTYPE_A,
   _CTYPE_U|_CTYPE_R|_CTYPE_G|_CTYPE_A,
   _CTYPE_U|_CTYPE_R|_CTYPE_G|_CTYPE_A,
   _CTYPE_U|_CTYPE_R|_CTYPE_G|_CTYPE_A,
   _CTYPE_U|_CTYPE_R|_CTYPE_G|_CTYPE_A,
   _CTYPE_U|_CTYPE_R|_CTYPE_G|_CTYPE_A,
   _CTYPE_U|_CTYPE_R|_CTYPE_G|_CTYPE_A,
   _CTYPE_U|_CTYPE_R|_CTYPE_G|_CTYPE_A,
   _CTYPE_U|_CTYPE_R|_CTYPE_G|_CTYPE_A,
   _CTYPE_U|_CTYPE_R|_CTYPE_G|_CTYPE_A,
   _CTYPE_U|_CTYPE_R|_CTYPE_G|_CTYPE_A,
   _CTYPE_U|_CTYPE_R|_CTYPE_G|_CTYPE_A,
   _CTYPE_P|_CTYPE_R|_CTYPE_G,
   _CTYPE_P|_CTYPE_R|_CTYPE_G,
   _CTYPE_P|_CTYPE_R|_CTYPE_G,
   _CTYPE_P|_CTYPE_R|_CTYPE_G,
   _CTYPE_P|_CTYPE_R|_CTYPE_G,
   _CTYPE_P|_CTYPE_R|_CTYPE_G,
   _CTYPE_L|_CTYPE_X|_CTYPE_R|_CTYPE_G|_CTYPE_A|10,
   _CTYPE_L|_CTYPE_X|_CTYPE_R|_CTYPE_G|_CTYPE_A|11,
   _CTYPE_L|_CTYPE_X|_CTYPE_R|_CTYPE_G|_CTYPE_A|12,
   _CTYPE_L|_CTYPE_X|_CTYPE_R|_CTYPE_G|_CTYPE_A|13,
   _CTYPE_L|_CTYPE_X|_CTYPE_R|_CTYPE_G|_CTYPE_A|14,
   _CTYPE_L|_CTYPE_X|_CTYPE_R|_CTYPE_G|_CTYPE_A|15,
   _CTYPE_L|_CTYPE_R|_CTYPE_G|_CTYPE_A,
   _CTYPE_L|_CTYPE_R|_CTYPE_G|_CTYPE_A,
   _CTYPE_L|_CTYPE_R|_CTYPE_G|_CTYPE_A,
   _CTYPE_L|_CTYPE_R|_CTYPE_G|_CTYPE_A,
   _CTYPE_L|_CTYPE_R|_CTYPE_G|_CTYPE_A,
   _CTYPE_L|_CTYPE_R|_CTYPE_G|_CTYPE_A,
   _CTYPE_L|_CTYPE_R|_CTYPE_G|_CTYPE_A,
   _CTYPE_L|_CTYPE_R|_CTYPE_G|_CTYPE_A,
   _CTYPE_L|_CTYPE_R|_CTYPE_G|_CTYPE_A,
   _CTYPE_L|_CTYPE_R|_CTYPE_G|_CTYPE_A,
   _CTYPE_L|_CTYPE_R|_CTYPE_G|_CTYPE_A,
   _CTYPE_L|_CTYPE_R|_CTYPE_G|_CTYPE_A,
   _CTYPE_L|_CTYPE_R|_CTYPE_G|_CTYPE_A,
   _CTYPE_L|_CTYPE_R|_CTYPE_G|_CTYPE_A,
   _CTYPE_L|_CTYPE_R|_CTYPE_G|_CTYPE_A,
   _CTYPE_L|_CTYPE_R|_CTYPE_G|_CTYPE_A,
   _CTYPE_L|_CTYPE_R|_CTYPE_G|_CTYPE_A,
   _CTYPE_L|_CTYPE_R|_CTYPE_G|_CTYPE_A,
   _CTYPE_L|_CTYPE_R|_CTYPE_G|_CTYPE_A,
   _CTYPE_L|_CTYPE_R|_CTYPE_G|_CTYPE_A,
   _CTYPE_P|_CTYPE_R|_CTYPE_G,
   _CTYPE_P|_CTYPE_R|_CTYPE_G,
   _CTYPE_P|_CTYPE_R|_CTYPE_G,
   _CTYPE_P|_CTYPE_R|_CTYPE_G,
   _CTYPE_C,
  },
  {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
   0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
   0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
   0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f,
   0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
   0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f,
   0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
   0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f,
   0x40, 'a', 'b', 'c', 'd', 'e', 'f', 'g',
   'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
   'p', 'q', 'r', 's', 't', 'u', 'v', 'w',
   'x', 'y', 'z', 0x5b, 0x5c, 0x5d, 0x5e, 0x5f,
   0x60, 'a', 'b', 'c', 'd', 'e', 'f', 'g',
   'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
   'p', 'q', 'r', 's', 't', 'u', 'v', 'w',
   'x', 'y', 'z', 0x7b, 0x7c, 0x7d, 0x7e, 0x7f,
   0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87,
   0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f,
   0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97,
   0x98, 0x99, 0x9a, 0x9b, 0x9c, 0x9d, 0x9e, 0x9f,
   0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7,
   0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf,
   0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xb5, 0xb6, 0xb7,
   0xb8, 0xb9, 0xba, 0xbb, 0xbc, 0xbd, 0xbe, 0xbf,
   0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7,
   0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf,
   0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0xd5, 0xd6, 0xd7,
   0xd8, 0xd9, 0xda, 0xdb, 0xdc, 0xdd, 0xde, 0xdf,
   0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7,
   0xe8, 0xe9, 0xea, 0xeb, 0xec, 0xed, 0xee, 0xef,
   0xf0, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7,
   0xf8, 0xf9, 0xfa, 0xfb, 0xfc, 0xfd, 0xfe, 0xff,
  },
  {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
   0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
   0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
   0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f,
   0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
   0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f,
   0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
   0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f,
   0x40, 'A', 'B', 'C', 'D', 'E', 'F', 'G',
   'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
   'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W',
   'X', 'Y', 'Z', 0x5b, 0x5c, 0x5d, 0x5e, 0x5f,
   0x60, 'A', 'B', 'C', 'D', 'E', 'F', 'G',
   'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
   'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W',
   'X', 'Y', 'Z', 0x7b, 0x7c, 0x7d, 0x7e, 0x7f,
   0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87,
   0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f,
   0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97,
   0x98, 0x99, 0x9a, 0x9b, 0x9c, 0x9d, 0x9e, 0x9f,
   0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7,
   0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf,
   0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xb5, 0xb6, 0xb7,
   0xb8, 0xb9, 0xba, 0xbb, 0xbc, 0xbd, 0xbe, 0xbf,
   0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7,
   0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf,
   0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0xd5, 0xd6, 0xd7,
   0xd8, 0xd9, 0xda, 0xdb, 0xdc, 0xdd, 0xde, 0xdf,
   0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7,
   0xe8, 0xe9, 0xea, 0xeb, 0xec, 0xed, 0xee, 0xef,
   0xf0, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7,
   0xf8, 0xf9, 0xfa, 0xfb, 0xfc, 0xfd, 0xfe, 0xff,
  },
};


int
asprintf_l(char **strp, locale_t loc, const char *fmt, ...) {
  va_list args;
  int res;

  va_start(args, fmt);
  res = vasprintf(strp, fmt, args);
  va_end(args);

  return res;
}


int
iswctype_l(wint_t wc, wctype_t desc, locale_t loc) {
  return iswctype(wc, desc);
}


size_t
mbsrtowcs_l(wchar_t *dest, const char **src, size_t n, mbstate_t *ps,
	    locale_t loc) {
  return mbsrtowcs(dest, src, n, ps);
}


int
snprintf_l(char *s, size_t n, locale_t loc, const char *format, ...) {
  va_list args;
  int res;

  va_start(args, format);
  res = vsnprintf(s, n, format, args);
  va_end(args);

  return res;
}


int
sscanf_l(const char *s, const char *format, locale_t loc, ...) {
  va_list args;
  int res;

  va_start(args, loc);
  res = vsscanf(s, format, args);
  va_end(args);

  return res;
}


int
strcoll_l(const char *s1, const char *s2, locale_t loc) {
  return strcoll(s1, s2);
}


size_t
strftime_l(char *s, size_t maxsize, const char *format,
	   const struct tm *timeptr, locale_t loc) {
  return strftime(s, maxsize, format, timeptr);
}


double
strtod_l(const char *nptr, char **endptr, locale_t loc) {
  return strtod(nptr, endptr);
}


float
strtof_l(const char *nptr, char **endptr, locale_t loc) {
  return strtof(nptr, endptr);
}


long double
strtold_l(const char *nptr, char **endptr, locale_t loc) {
  return strtold(nptr, endptr);
}


long long
strtoll_l(const char *nptr, char **endptr, int base, locale_t loc) {
  return strtoll(nptr, endptr, base);
}


size_t
strxfrm_l(char *dest, const char *src, size_t n, locale_t loc) {
  return strxfrm(dest, src, n);
}


int
wcscoll_l(const wchar_t *ws1, const wchar_t *ws2, locale_t loc) {
  return wcscoll(ws1, ws2);
}


size_t
wcsxfrm_l(wchar_t *dest, const wchar_t *src, size_t n, locale_t loc) {
  return wcsxfrm(dest, src, n);
}


locale_t
newlocale(int mask, const char *locale, locale_t base) {
  return calloc(sizeof(int), 1);
}


int
freelocale(locale_t loc) {
  if(loc) {
    free(loc);
    return 0;
  }
  return -1;
}


void*
catopen(const char *name, int flag) {
  return (void*)0x1;
}


int
catclose(void *catalog) {
  return 0;
}


char*
catgets(void *catalog, int set_no, int message_no, const char *message) {
  return strdup(message);
}


wint_t
btowc_l(int c, locale_t loc) {
  return (wint_t)c;
}


struct lconv*
localeconv_l(locale_t loc) {
  return localeconv();
}


size_t
mbrlen_l(const char *s, size_t n, mbstate_t *ps, locale_t loc) {
  return mbrlen(s, n, ps);
}


size_t
mbrtowc_l(wchar_t *pwc, const char *s, size_t n, mbstate_t *ps, locale_t loc) {
  return mbrtowc(pwc, s, n, ps);
}


size_t
mbsnrtowcs_l(wchar_t *dst, const char **src, size_t nmc, size_t len,
	     mbstate_t *ps, locale_t loc) {
  return mbsnrtowcs(dst, src, nmc, len, ps);
}


int
mbtowc_l(wchar_t *pwc, const char *s, size_t n, locale_t loc) {
  return mbtowc(pwc, s, n);
}


unsigned long long
strtoull_l(const char *nptr, char **endptr, int base, locale_t loc) {
  return strtoull(nptr, endptr, base);
}


int
wcrtomb_l(char *s, wchar_t wc, mbstate_t *ps, locale_t loc) {
  return wcrtomb(s, wc, ps);
}


size_t
wcsnrtombs_l(char *dest, const wchar_t **src, size_t nwc, size_t len,
	     mbstate_t *ps, locale_t loc) {
  return wcsnrtombs(dest, src, nwc, len, ps);
}


int
wctob_l(wint_t c, locale_t loc) {
  return (int)c;
}


//
// Gotta love the design of FreeBSD libc :D
//


__ct_rune_t
___toupper(__ct_rune_t c) {
  return toupper(c);
}


int
__toupper_l(int c, locale_t loc) {
  return toupper(c);
}


__ct_rune_t
___toupper_l(__ct_rune_t c, locale_t loc) {
  return toupper(c);
}


__ct_rune_t
___tolower(__ct_rune_t c) {
  return tolower(c);
}


int
__tolower_l(int c, locale_t loc) {
  return tolower(c);
}


__ct_rune_t
___tolower_l(__ct_rune_t c, locale_t loc) {
  return tolower(c);
}


int ___mb_cur_max(void) {
  return __mb_cur_max;
}


int ___mb_cur_max_l(locale_t loc) {
  return __mb_cur_max;
}


//
//TODO: rune stuff
//


_RuneLocale*
__runes_for_locale(locale_t locale, int *mb_sb_limit) {
  return (_RuneLocale*)&_DefaultRuneLocale;
}


const _RuneLocale *
__getCurrentRuneLocale(void) {
  return &_DefaultRuneLocale;
}


unsigned long
___runetype(__ct_rune_t c) {
  return 0;
}


unsigned long
___runetype_l(__ct_rune_t c, locale_t loc) {
  return 0;
}
