#pragma once




#include "nova_platforms.h"


typedef struct nova_Sound nova_Sound;




int nova_OpenAudioEngine_I();

void nova_CloseAudioEngine_I();



NOVA_API
nova_Sound* nova_SoundLoad(const char* path);

NOVA_API
void nova_SoundPlay(nova_Sound* sound);

NOVA_API
void nova_SoundPause(nova_Sound* sound);


NOVA_API
void nova_SoundSetLoop(nova_Sound* sound, int loop);

NOVA_API
void nova_SoundSetVolume(nova_Sound* sound, float volume);

NOVA_API
void nova_SoundUnload(nova_Sound* sound);