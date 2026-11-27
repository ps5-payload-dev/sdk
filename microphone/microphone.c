#include "ps5/microphone.h"
#include "ps5/audioin.h"

#include <errno.h>
#include <limits.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MIC_DEFAULT_GRAIN 256u
#define MIC_DEFAULT_QUEUE 4096u
#define MIC_MUTED_BITS 5

struct ps5_microphone {
  int handle;
  pthread_t thread;
  pthread_mutex_t mutex;
  pthread_cond_t available;
  int mutex_ready;
  int cond_ready;
  int thread_started;
  int stopping;
  int finished;
  int silent_state;
  int last_error;
  unsigned rate;
  unsigned grain;
  size_t capacity;
  size_t head;
  size_t count;
  int16_t *queue;
  uint64_t captured;
  uint64_t delivered;
  uint64_t dropped;
};

static void
wipe_samples(int16_t *samples, size_t count) {
  volatile int16_t *p = samples;
  while(count--) *p++ = 0;
}

static void
queue_clear(ps5_microphone_t *mic) {
  mic->dropped += mic->count;
  mic->head = 0;
  mic->count = 0;
  wipe_samples(mic->queue, mic->capacity);
}

static void
queue_push(ps5_microphone_t *mic, const int16_t *samples) {
  size_t i;
  for(i = 0; i < mic->grain; i++) {
    size_t tail;
    if(mic->count == mic->capacity) {
      mic->head = (mic->head + 1) % mic->capacity;
      mic->count--;
      mic->dropped++;
    }
    tail = (mic->head + mic->count) % mic->capacity;
    mic->queue[tail] = samples[i];
    mic->count++;
  }
  mic->captured += mic->grain;
}

static void *
capture_thread(void *arg) {
  ps5_microphone_t *mic = arg;
  int16_t *block = malloc(mic->grain * sizeof(*block));
  if(!block) {
    pthread_mutex_lock(&mic->mutex);
    mic->last_error = -ENOMEM;
    mic->finished = 1;
    pthread_cond_broadcast(&mic->available);
    pthread_mutex_unlock(&mic->mutex);
    return NULL;
  }

  for(;;) {
    int rc = sceAudioInInput(mic->handle, block);
    int silent;
    if(rc < 0) {
      pthread_mutex_lock(&mic->mutex);
      if(!mic->stopping) mic->last_error = rc;
      mic->finished = 1;
      pthread_cond_broadcast(&mic->available);
      pthread_mutex_unlock(&mic->mutex);
      break;
    }
    silent = sceAudioInGetSilentState(mic->handle);
    pthread_mutex_lock(&mic->mutex);
    if(mic->stopping) {
      pthread_mutex_unlock(&mic->mutex);
      break;
    }
    if(silent < 0) {
      mic->last_error = silent;
      mic->finished = 1;
      pthread_cond_broadcast(&mic->available);
      pthread_mutex_unlock(&mic->mutex);
      break;
    }
    if(silent != mic->silent_state && (silent & MIC_MUTED_BITS))
      queue_clear(mic);
    mic->silent_state = silent;
    if(silent & MIC_MUTED_BITS) memset(block, 0, mic->grain * sizeof(*block));
    queue_push(mic, block);
    pthread_cond_broadcast(&mic->available);
    pthread_mutex_unlock(&mic->mutex);
  }
  wipe_samples(block, mic->grain);
  free(block);
  return NULL;
}

static int
open_port(int user, unsigned grain, unsigned rate) {
  static const int types[] = {0, 1, 5};
  size_t i;
  int handle = -1;
  for(i = 0; i < sizeof(types) / sizeof(types[0]) && handle < 0; i++)
    handle = sceAudioInOpen(user, types[i], 0, grain, rate, 0);
  return handle;
}

int
ps5_microphone_open(ps5_microphone_t **out,
                    const ps5_microphone_options_t *options) {
  ps5_microphone_t *mic;
  unsigned rate, grain, queue_frames;
  int rc, handle = -1;
  if(!out || !options) return -EINVAL;
  *out = NULL;
  grain = options->frames_per_read ? options->frames_per_read : MIC_DEFAULT_GRAIN;
  queue_frames = options->queue_frames ? options->queue_frames : MIC_DEFAULT_QUEUE;
  if(!grain || queue_frames < grain) return -EINVAL;
  if(options->sample_rate && options->sample_rate != 48000 && options->sample_rate != 16000)
    return -EINVAL;
  rc = sceAudioInInit();
  if(rc < 0 && (uint32_t)rc != 0x8026000eu &&
     (uint32_t)rc != 0x8026000cu) return rc;
  if(options->sample_rate) {
    handle = open_port(options->user_id, grain, options->sample_rate);
    rate = options->sample_rate;
  } else {
    handle = open_port(options->user_id, grain, 48000);
    rate = 48000;
    if(handle < 0) {
      handle = open_port(options->user_id, grain, 16000);
      rate = 16000;
    }
  }
  if(handle < 0) return handle;
  mic = calloc(1, sizeof(*mic));
  if(!mic) { sceAudioInClose(handle); return -ENOMEM; }
  mic->queue = malloc(queue_frames * sizeof(*mic->queue));
  if(!mic->queue) { sceAudioInClose(handle); free(mic); return -ENOMEM; }
  mic->handle = handle;
  mic->rate = rate;
  mic->grain = grain;
  mic->capacity = queue_frames;
  mic->silent_state = 0;
  rc = pthread_mutex_init(&mic->mutex, NULL);
  if(rc) goto fail;
  mic->mutex_ready = 1;
  rc = pthread_cond_init(&mic->available, NULL);
  if(rc) goto fail;
  mic->cond_ready = 1;
  rc = pthread_create(&mic->thread, NULL, capture_thread, mic);
  if(rc) goto fail;
  mic->thread_started = 1;
  *out = mic;
  return 0;

fail:
  if(mic->cond_ready) pthread_cond_destroy(&mic->available);
  if(mic->mutex_ready) pthread_mutex_destroy(&mic->mutex);
  sceAudioInClose(handle);
  free(mic->queue);
  free(mic);
  return -rc;
}

static void
deadline_after(struct timespec *deadline, unsigned timeout_ms) {
  clock_gettime(CLOCK_REALTIME, deadline);
  deadline->tv_sec += timeout_ms / 1000;
  deadline->tv_nsec += (long)(timeout_ms % 1000) * 1000000L;
  if(deadline->tv_nsec >= 1000000000L) {
    deadline->tv_sec++;
    deadline->tv_nsec -= 1000000000L;
  }
}

int
ps5_microphone_read(ps5_microphone_t *mic, int16_t *samples,
                    size_t capacity_frames, unsigned timeout_ms) {
  size_t n, i;
  int rc = 0;
  struct timespec deadline;
  if(!mic || (!samples && capacity_frames)) return -EINVAL;
  if(!capacity_frames) return 0;
  if(capacity_frames > INT_MAX) capacity_frames = INT_MAX;
  if(timeout_ms != UINT32_MAX && timeout_ms) deadline_after(&deadline, timeout_ms);
  pthread_mutex_lock(&mic->mutex);
  while(!mic->count && !mic->finished && !mic->stopping) {
    if(timeout_ms == 0) break;
    if(timeout_ms == UINT32_MAX) rc = pthread_cond_wait(&mic->available, &mic->mutex);
    else rc = pthread_cond_timedwait(&mic->available, &mic->mutex, &deadline);
    if(rc == ETIMEDOUT) break;
    if(rc) { pthread_mutex_unlock(&mic->mutex); return -rc; }
  }
  n = capacity_frames < mic->count ? capacity_frames : mic->count;
  for(i = 0; i < n; i++) samples[i] = mic->queue[(mic->head + i) % mic->capacity];
  mic->head = (mic->head + n) % mic->capacity;
  mic->count -= n;
  mic->delivered += n;
  rc = mic->last_error;
  pthread_mutex_unlock(&mic->mutex);
  if(n) return (int)n;
  return rc < 0 ? rc : 0;
}

void
ps5_microphone_get_stats(ps5_microphone_t *mic, ps5_microphone_stats_t *stats) {
  if(!mic || !stats) return;
  pthread_mutex_lock(&mic->mutex);
  stats->captured_frames = mic->captured;
  stats->delivered_frames = mic->delivered;
  stats->dropped_frames = mic->dropped;
  stats->sample_rate = mic->rate;
  stats->frames_per_read = mic->grain;
  stats->silent_state = mic->silent_state;
  stats->last_error = mic->last_error;
  pthread_mutex_unlock(&mic->mutex);
}

void
ps5_microphone_close(ps5_microphone_t *mic) {
  if(!mic) return;
  pthread_mutex_lock(&mic->mutex);
  mic->stopping = 1;
  mic->finished = 1;
  queue_clear(mic);
  pthread_cond_broadcast(&mic->available);
  pthread_mutex_unlock(&mic->mutex);
  if(mic->thread_started) pthread_join(mic->thread, NULL);
  sceAudioInClose(mic->handle);
  pthread_cond_destroy(&mic->available);
  pthread_mutex_destroy(&mic->mutex);
  free(mic->queue);
  free(mic);
}
