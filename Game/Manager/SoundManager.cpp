#include "stdafx.h"
#include "SoundManager.h"

SoundManager* SoundManager::SM = nullptr;

SoundManager::SoundManager()
{
	Volume = 0.0f;
	LoopLength = 850000 / 44100.0f;

	BGM.Content = STR.BGM.c_str();
	BGM.loop = true;

	SE_Decide.Content = "SE_Decide";
	SE_Decide.loop = false;

	SE_Move.Content = "SE_Move";
	SE_Move.loop = false;

	SetVolume(ConstValue::DefVolume);
}

SoundManager::~SoundManager() {}

SoundManager*& SoundManager::Get()
{
	if (SM == nullptr) SM = new SoundManager();
	return SM;
}


void SoundManager::Destroy()
{
	if (SM == nullptr) return;
	delete SM;
	SM = nullptr;
}


void SoundManager::SetBGM(std::string const& title, UINT32 const& Highlight)
{ 
	if(title != "") STR.BGM = title;
	BGM.Content = STR.BGM.c_str();
	BGM.volume = Volume;
	LoopLength = 850000 / 44100.0f;
	if (Highlight)
	{
		BGM.loop = true;
		BGM.loopBegin = Highlight;
		BGM.loopLength = 850000;
		BGM.volume = 0.0f;
	}
	else BGM.loop = false;
}

void SoundManager::SetVolume(float const& volume)
{
	Volume = volume;

	BGM.volume = Volume;
	SE_Decide.volume = Volume;
	SE_Move.volume = Volume;
}

void SoundManager::SetFadeIO()
{
	LoopLength -= Time::Get::Delta();
	if (BGM.isLoopEnd()) LoopLength = 850000 / 44100.0f;

	//곡이 끝나기 2초전 페이드아웃
	if (LoopLength < 2.0f)
	{
		BGM.volume -= Volume * Time::Get::Delta() / 2;
		BGM.SetVolume();
	}
	//페이드 인
	else if (BGM.volume < Volume)
	{
		BGM.volume += Volume * Time::Get::Delta() / 2;
		BGM.SetVolume();
	}
}


