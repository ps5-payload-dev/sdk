/* Empirical libSceAudioIn ABI used by PS5 homebrew. Not an official Sony header. */
#ifndef PS5_AUDIOIN_H
#define PS5_AUDIOIN_H

#ifdef __cplusplus
extern "C" {
#endif

int sceAudioInInit(void);
int sceAudioInOpen(int user_id, int type, int index, unsigned length,
                   unsigned rate, unsigned format);
int sceAudioInInput(int handle, void *samples);
int sceAudioInGetSilentState(int handle);
int sceAudioInClose(int handle);

#ifdef __cplusplus
}
#endif
#endif
