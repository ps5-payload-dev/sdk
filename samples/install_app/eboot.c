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


long
__syscall(long n, ...) {
  long a1 = 0, a2 = 0, a3 = 0, a4 = 0, a5 = 0, a6 = 0;
  __builtin_va_list ap;
  unsigned long ret;
  char iserror;

  __builtin_va_start(ap, n);
  a1 = __builtin_va_arg(ap, long);
  a2 = __builtin_va_arg(ap, long);
  a3 = __builtin_va_arg(ap, long);
  a4 = __builtin_va_arg(ap, long);
  a5 = __builtin_va_arg(ap, long);
  a6 = __builtin_va_arg(ap, long);
  __builtin_va_end(ap);

  register long r10 __asm__("r10") = a4;
  register long r8  __asm__("r8")  = a5;
  register long r9  __asm__("r9")  = a6;

  __asm__ __volatile__("syscall"
		       : "=a"(ret), "=@ccc"(iserror), "+r"(r10), "+r"(r8), "+r"(r9)
		       : "a"(n), "D"(a1), "S"(a2), "d"(a3)
		       : "rcx", "r11", "memory");

  return iserror ? -ret : ret;
}


int
klog(const char *s) {
  return __syscall(0x259, 7, s, 0);
}


int
main(void) {
  klog("Hello, world!\n");
  return 0;
}


void
_start(void) {
  __syscall(1, main()); // exit
  __builtin_trap();
}
