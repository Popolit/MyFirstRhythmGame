#include "stdafx.h"
#include "SoundManager.h"

SoundManager* SoundManager::Instance = nullptr;

//싱글톤 생성자
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

//생성, 인스턴스 반환
SoundManager*& SoundManager::Get()
{
	if (Instance == nullptr) Instance = new SoundManager();
	return Instance;
}

//싱글톤 파괴자
void SoundManager::Destroy()
{
	if (Instance == nullptr) return;
	delete Instance;
	Instance = nullptr;
}

//BGM을 변경, Highligt가 있으면 하이라이트 구간을 설정
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

//전체 볼륨 조정
void SoundManager::SetVolume(UINT const& volume)
{
	Volume = volume / 100.0f;

	BGM.volume = Volume;
	SE_Decide.volume = Volume;
	SE_Move.volume = Volume;
}

//노래가 페이드 인/아웃 하도록 함
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


