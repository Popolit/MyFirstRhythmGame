#pragma once
#include "ConstValue.h"

class SoundManager
{
public:
	float Volume;
	float LoopLength;
	struct 
	{
		std::string BGM;
		std::string NowPlaying;
	}STR;

	Sound::Sound BGM;
	Sound::Sound NowPlaying;
	Sound::Sound SE_Move;
	Sound::Sound SE_Decide;
public:
	SoundManager();
	void SetBGM(std::string const& title, UINT32 const& Highlight = 0);
	void SetVolume(float const& volume);
	void SetFadeIO();
};

