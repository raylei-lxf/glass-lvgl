#ifndef _MEDIA_SPECTRUM_H_
#define _MEDIA_SPECTRUM_H_
#include "player_int.h"
#include "speex/speex_preprocess.h"

typedef struct spectrum_t{
	SpeexPreprocessState *handle;
	unsigned char *pcm_data;
	unsigned int samplerate;
	unsigned int channels;
	unsigned int size;
	int ps_size;
	int *ps_buffer;
	pthread_mutex_t mutex;
	int init_flag;
}spectrum_t;

void media_spectrum_deinit(void);
void media_spectrum_updata(AudioPcmData *audio_info);
int  *media_get_spectrum(void);
int media_get_spectrum_size(void);
void media_specturm_lock(void);
void media_specturm_unlock(void);

#endif
