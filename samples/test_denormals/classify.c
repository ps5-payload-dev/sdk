/* Copyright (C) 2026 Mihawk
 * SPDX-License-Identifier: GPL-3.0-or-later
 */
#include <math.h>

/* A separate translation unit prevents constant folding at the call site. */
int
classify(float value) {
  return __builtin_fpclassify(FP_NAN, FP_INFINITE, FP_NORMAL,
                             FP_SUBNORMAL, FP_ZERO, value);
}
