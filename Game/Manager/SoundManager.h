#pragma once
#include "ConstValue.h"

//사운드를 총괄하는 클래스
class SoundManager
{
private:
	static SoundManager* Instance ;
	
public:
	float Volume;
	float LoopLength;
	struct 
	{
		std::string BGM;
	}STR;

	Sound::Sound BGM;
	Sound::Sound SE_Move;
	Sound::Sound SE_Decide;

private:
	SoundManager();
	~SoundManager();
public:
	static SoundManager*& Get();
	static void Destroy();
	void SetBGM(std::string const& title = "", UINT32 const& Highlight = 0);
	void SetVolume(UINT const& volume);
	void SetFadeIO();
};

