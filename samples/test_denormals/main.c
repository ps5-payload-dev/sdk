/* Copyright (C) 2026 Mihawk
 * SPDX-License-Identifier: GPL-3.0-or-later
 */
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

int classify(float value);

int
main(void) {
  unsigned previous, ieee;
  uint32_t bits = 1; /* Smallest positive IEEE binary32 subnormal. */
  float value;
  memcpy(&value, &bits, sizeof(value));
  __asm__ volatile("stmxcsr %0" : "=m"(previous));
  ieee = previous & ~0x8040u; /* Disable FTZ and DAZ for this test. */
  __asm__ volatile("ldmxcsr %0" : : "m"(ieee) : "memory");
  const int actual = classify(value);
  __asm__ volatile("ldmxcsr %0" : : "m"(previous) : "memory");
  printf("classification=%d, expected FP_SUBNORMAL=%d\n", actual, FP_SUBNORMAL);
  return actual != FP_SUBNORMAL;
}
