///******************************************************************************/
///*!
// \file   SoundSystem.c
// \proj   Dark Rising
// \author Dean Hulse
// \par    Course: GAM150
// \par    All content ?2014 DigiPen (USA) Corporation, all rights reserved.
// \brief  Debugging System defined
// */
///******************************************************************************/
#include <Windows.h>
#include "SoundSystem.h"

void SoundSystemLoad(void)
{
	Result = FMOD_System_Create(&System);

	Result = FMOD_System_Init(System, 10, FMOD_INIT_NORMAL, NULL);
}

int SoundAdd(const char* filePath, const int loopStyle, const unsigned int soundList)
{
	Result = FMOD_System_CreateSound(System, filePath, loopStyle, 0, &Sound[soundList]);

	if(Result)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void SoundPlay(const unsigned int soundList)
{
	Result = FMOD_System_PlaySound(System, FMOD_CHANNEL_FREE, Sound[soundList], 0, &Channel[soundList]);
	SetVolume(SOUND_1, 0.5);
}

void SoundPausePlay(const unsigned int soundList)
{
	Result = FMOD_Channel_GetPaused(Channel[soundList], &Paused[soundList]);

	if(Paused[soundList])
	{
		FMOD_Channel_SetPaused(Channel[soundList], 0);
	}
	else
	{
		FMOD_Channel_SetPaused(Channel[soundList], 1);
	}
}

void SoundStop(const unsigned int soundList)
{
	if(SoundIsPlaying(soundList))
	{
		Result = FMOD_Channel_Stop(Channel[soundList]);
	}
}

int SoundIsPlaying(const unsigned int soundList)
{
	Result = FMOD_Channel_IsPlaying(Channel[soundList], &Playing[soundList]);
	return Playing[soundList];
}

void SetVolume(const unsigned int soundList, float volume)
{
	FMOD_Channel_SetVolume(Channel[soundList], volume);
}

float GetVolume(const unsigned int soundList)
{
	FMOD_Channel_GetVolume(Channel[soundList], &Volume[soundList]);

	return Volume[soundList];
}

void SoundSystemExit(void)
{
	Result = FMOD_System_Close(System);
}

void SoundUpdate (void)
{
	Result = FMOD_System_Update(System);
}