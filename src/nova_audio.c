#include "nova_audio.h"
#include "nova_common.h"
#include "nova_types.h"



#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"


#include <stdlib.h>




typedef struct nova_Sound {
    ma_sound MAsound;
} nova_Sound;



static ma_engine nova_AudioEngine_I;




int nova_OpenAudioEngine_I()
{
    if (ma_engine_init(NULL, &nova_AudioEngine_I) != MA_SUCCESS) {
        NOVA_LOG_ERROR("Audio Initialization Failed!");
        return NOVA_FALSE;
    }

    return NOVA_TRUE;
}




void nova_CloseAudioEngine_I()
{
    ma_engine_uninit(&nova_AudioEngine_I);
}










nova_Sound* nova_SoundLoad(const char* path)
{
    nova_Sound* sound = NOVA_MALLOC(nova_Sound);
    if (NOVA_NOT sound) {
        NOVA_LOGV_WARN("Memory allocation failed while allocating sound for file: %s", path);
        goto SoundLoadingFailure;
    }

    int result =  ma_sound_init_from_file(
        &nova_AudioEngine_I,
        path,
        0,
        NULL,
        NULL,
        &sound->MAsound
    ) == MA_SUCCESS;


    if (NOVA_NOT result) {
        NOVA_LOGV_WARN("Not able to initialize miniaudio sound!");
        goto SoundLoadingFailure;
    }

    return sound;


SoundLoadingFailure:
    NOVA_LOG_WARN("Not able to load sound file: %s", path);
    return NULL;

}





void nova_SoundPlay(nova_Sound* sound)
{
    ma_sound_start(&sound->MAsound);
}



void nova_SoundPause(nova_Sound* sound)
{
    ma_sound_stop(&sound->MAsound);
}



void nova_SoundSetLoop(nova_Sound* sound, int loop)
{
    ma_sound_set_looping(&sound->MAsound, loop);
}



void nova_SoundSetVolume(nova_Sound* sound, float volume)
{
    ma_sound_set_volume(&sound->MAsound, volume);
}




void nova_SoundUnload(nova_Sound* sound)
{
    if (NOVA_NOT sound) {
        NOVA_LOG_WARN("No sound provided!");
        return;
    }


    ma_sound_uninit(&sound->MAsound);
}