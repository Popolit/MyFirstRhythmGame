#include "stdafx.h"
#include "SoundManager.h"

SoundManager::SoundManager()
{
	BGM.Content = STR.BGM.data();
	BGM.loop = true;

	NowPlaying.Content = STR.NowPlaying.data();
	NowPlaying.loopLength = 0;
	NowPlaying.loop = true;

	SE_Decide.Content = "SE_Decide";
	SE_Decide.loop = false;
	
	SE_Move.Content = "SE_Move";
	SE_Move.loop = false;
}

void SoundManager::SetBGM(std::string const& title, UINT32 const& Highlight) 
{ 
	STR.BGM = title; 
	if (Highlight)
	{
		BGM.loop = true;
		BGM.loopBegin = Highlight;
		BGM.loopLength = 850000;
		BGM.SetVolume();
	}
}
void SoundManager::SetNowPlaying(std::string const& title) { STR.NowPlaying = title; }

void SoundManager::SetVolume(float const& volume)
{
	Volume = volume;

	BGM.volume = Volume;
	NowPlaying.volume = Volume;
	SE_Decide.volume = Volume;
	SE_Move.volume = Volume;
}

void SoundManager::SetHighlight(UINT32 const& Highlight)
{
	NowPlaying.loop = true;
	NowPlaying.loopBegin = Highlight;
}

