/* PS5 Payload SDK - real-time PCM capture from the system-selected microphone.
 * Copyright (C) 2026 Mihawk
 * SPDX-License-Identifier: GPL-3.0-or-later
 */
#ifndef PS5_MICROPHONE_H
#define PS5_MICROPHONE_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ps5_microphone ps5_microphone_t;

typedef struct ps5_microphone_options {
  int user_id;                 /* UserService id; caller selects the user. */
  unsigned sample_rate;        /* 48000 or 16000; 0 tries both in that order. */
  unsigned frames_per_read;    /* 0 selects 256. */
  unsigned queue_frames;       /* 0 selects 4096; must hold >= one read. */
} ps5_microphone_options_t;

typedef struct ps5_microphone_stats {
  uint64_t captured_frames;
  uint64_t delivered_frames;
  uint64_t dropped_frames;
  unsigned sample_rate;
  unsigned frames_per_read;
  int silent_state;
  int last_error;
} ps5_microphone_stats_t;

/* Opens the system-routed input as signed 16-bit mono PCM. Returns 0 or a
 * negative system/API error. Link libps5microphone.a and libSceAudioIn.so. */
int ps5_microphone_open(ps5_microphone_t **out,
                        const ps5_microphone_options_t *options);

/* Reads up to capacity_frames into samples. timeout_ms: 0 is nonblocking,
 * UINT32_MAX waits indefinitely. Returns frames read, 0 on timeout/closed,
 * or a negative error. */
int ps5_microphone_read(ps5_microphone_t *mic, int16_t *samples,
                        size_t capacity_frames, unsigned timeout_ms);

void ps5_microphone_get_stats(ps5_microphone_t *mic,
                              ps5_microphone_stats_t *stats);
void ps5_microphone_close(ps5_microphone_t *mic);

#ifdef __cplusplus
}
#endif
#endif
