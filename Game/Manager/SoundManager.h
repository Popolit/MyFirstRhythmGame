#pragma once
#include "ConstValue.h"

class SoundManager
{
public:
	float Volume;
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
	void SetNowPlaying(std::string const& title);
	void SetVolume(float const& volume);
	void SetHighlight(UINT32 const& Highlight);
};

