/* Copyright (C) 2023 John Törnblom

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

#include <stdio.h>
#include <string.h>
#include <ps5/kernel.h>

// exclude null terminator
#define sizeof_1(a) (sizeof(a) - 1)

typedef struct notify_request {
  char useless1[45];
  char message[1024];
  char useless2[2051];
} notify_request_t;

int sceKernelSendNotificationRequest(int, notify_request_t*, size_t, int);

int
main() {
  notify_request_t req;
  bzero(&req, sizeof(req));
  const uint32_t sdk = kernel_get_fw_version();
  snprintf(req.message, sizeof_1(req.message), "SDK Version: 0x%08x", sdk);

  return sceKernelSendNotificationRequest(0, &req, sizeof req, 0);
}
