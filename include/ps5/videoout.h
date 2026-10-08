/* Copyright (C) 2026 Mihawk
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 * VideoOut declarations used by PS5 homebrew presentation paths. Arguments
 * named reserved are passed as zero. Opaque attributes and status records
 * are kept opaque until their full layouts have been established.
 */
#ifndef PS5_VIDEOOUT_H
#define PS5_VIDEOOUT_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define PS5_VIDEO_OUT_USER_SYSTEM 0xff

#define PS5_VIDEO_OUT_PIXEL_FORMAT_B8G8R8A8_SDR UINT64_C(0x8000000000000000)

#define PS5_VIDEO_OUT_TILING_64KB_R_X 0u

/* Opaque buffer attribute storage, zeroed before SetBufferAttribute2. */
#define PS5_VIDEO_OUT_ATTRIBUTE_BYTES 80

struct ps5_video_out_buffer {
   void *data;
   void *metadata;
   void *reserved[2];
};

/* Word 3 reports the argument of the latest displayed flip. */
#define PS5_VIDEO_OUT_FLIP_STATUS_WORDS 16
#define PS5_VIDEO_OUT_FLIP_STATUS_SHOWN_ARGUMENT 3

#define PS5_VIDEO_OUT_FLIP_VSYNC 1

#define PS5_VIDEO_OUT_ERROR_BUSY ((int)0x80290009)

/* High frame rate also requires title and display support. */
#define PS5_VIDEO_OUT_MODE_HIGH_FRAME_RATE 15u
#define PS5_VIDEO_OUT_MODE_RESTORE 1u

int sceVideoOutOpen(int32_t user, int32_t bus, int32_t index, const void *parameter);
int sceVideoOutClose(int32_t handle);

int sceVideoOutSetFlipRate(int32_t handle, int32_t rate);
void sceVideoOutSetBufferAttribute2(void *attribute, uint64_t pixel_format, uint32_t tiling,
                                    uint32_t width, uint32_t height, uint64_t reserved1,
                                    uint32_t reserved2, uint64_t reserved3);

int sceVideoOutRegisterBuffers2(int32_t handle, int32_t set, int32_t start,
                                struct ps5_video_out_buffer *buffers, int32_t count,
                                void *attribute, int32_t reserved, void *option);
int sceVideoOutUnregisterBuffers(int32_t handle, int32_t set);

int sceVideoOutSubmitFlip(int32_t handle, int32_t buffer_index, uint32_t mode, int64_t argument);
int sceVideoOutGetFlipStatus(int32_t handle, uint64_t status[PS5_VIDEO_OUT_FLIP_STATUS_WORDS]);

int sceVideoOutIsFlipPending(int32_t handle);
int sceVideoOutWaitVblank(int32_t handle);

int sceVideoOutIsOutputSupported(int32_t handle, uint32_t mode, const void *reserved1,
                                 const void *reserved2, const void *reserved3);
int sceVideoOutConfigureOutput(int32_t handle, uint32_t mode, const void *reserved1,
                               const void *reserved2, const void *reserved3);

#ifdef __cplusplus
}
#endif

#endif
