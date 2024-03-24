#include "media_spectrum.h"
#include "speex/speex_preprocess.h"

static spectrum_t mspectrum;

void media_spectrum_init(uint32_t samplerate, uint32_t channel, uint32_t size)
{
	int frame_size;
	spectrum_t *sp = &mspectrum;

	sp->samplerate = samplerate;
    sp->channels = channel;
    sp->size = size;

	frame_size = sp->size/(sp->channels*sizeof(short));
	sp->handle = speex_preprocess_state_init(frame_size, sp->samplerate);
	speex_preprocess_ctl(sp->handle, SPEEX_PREPROCESS_GET_PSD_SIZE, &sp->ps_size);
	if(!sp->ps_buffer)
	{
		sp->ps_buffer = (int *)malloc(sp->ps_size * sizeof(int));
	}
	if(!sp->pcm_data)
	{
		sp->pcm_data = malloc(sp->size);
	}
	pthread_mutex_init(&sp->mutex, NULL);
	sp->init_flag = 1;
	//printf("%s %d\n", __func__, __LINE__);
}


void media_spectrum_deinit(void)
{
	spectrum_t *sp = &mspectrum;

	if(sp->handle)
	{
		speex_preprocess_state_destroy(sp->handle);
	}
	if(sp->ps_buffer)
	{
		free(sp->ps_buffer);
	}
	if(sp->pcm_data)
	{
		free(sp->pcm_data);
	}
	pthread_mutex_destroy(&sp->mutex);
	memset(sp, 0, sizeof(spectrum_t));
}

void media_spectrum_updata(AudioPcmData *audio_info)
{
	int frame_size;
	spectrum_t *sp = &mspectrum;

    if ((sp->init_flag == 1) && ((sp->samplerate != audio_info->samplerate)
        || (sp->channels != audio_info->channels)
        || (sp->size != audio_info->nSize)))
    {
        media_spectrum_deinit();
    }

	if(!sp->init_flag)
	{
		media_spectrum_init(audio_info->samplerate, audio_info->channels, audio_info->nSize);
	}

	if(!audio_info->pData)
	{
		return;
	}

	speex_preprocess_estimate_update(sp->handle, (spx_int16_t *)audio_info->pData);

//	printf("%s %d\n", __func__, __LINE__);
	pthread_mutex_lock(&sp->mutex);
	speex_preprocess_ctl(sp->handle, SPEEX_PREPROCESS_GET_PSD, sp->ps_buffer);
	pthread_mutex_unlock(&sp->mutex);

	return;
}

void media_specturm_lock(void)
{
	spectrum_t *sp = &mspectrum;

	if(!sp->init_flag)
	{
		return;
	}
//	printf("%s %d\n", __func__, __LINE__);
	pthread_mutex_lock(&sp->mutex);
}

void media_specturm_unlock(void)
{
	spectrum_t *sp = &mspectrum;

	if(!sp->init_flag)
	{
		return;
	}
	//printf("%s %d\n", __func__, __LINE__);
	pthread_mutex_unlock(&sp->mutex);
}

int *media_get_spectrum(void)
{
	spectrum_t *sp = &mspectrum;

	if(!sp->init_flag)
	{
		return NULL;
	}
#if 0
	FILE *fd;
	char buffer[32];
	fd = fopen("/tmp/spectrum.log", "w+");
	for(int i=0; i<sp->ps_size; i++){
		memset(buffer, 0, sizeof(buffer));
		sprintf(buffer, "%u ", sp->ps_buffer[i]);
		fwrite(buffer,1, strlen(buffer),fd);
	}
	memset(buffer, 0, sizeof(buffer));
	sprintf(buffer, "\n");
	fwrite(buffer,1, strlen(buffer),fd);
	fclose(fd);
#endif
	//printf("%s %d\n", __func__, __LINE__);
	return sp->ps_buffer;
}

int media_get_spectrum_size(void)
{
	spectrum_t *sp = &mspectrum;
	int size = 0;

	if(!sp->init_flag)
	{
		return 0;
	}	
	//printf("%s %d\n", __func__, __LINE__);
	pthread_mutex_lock(&sp->mutex);
	size = sp->ps_size;
	pthread_mutex_unlock(&sp->mutex);

	return size;
}
