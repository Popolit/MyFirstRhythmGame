#include "stdafx.h"
#include "GameValue.h"
#include "Component/Chart.h"

namespace GameValue
{
	namespace 
	{
		//옵션
		int SyncValue = int();
		float SpeedValue = float();
		size_t MappedKeys[4] = { 0, };
		float Volume = float();

		//공용 자원
		std::string BGMTitle;
		Chart* pCh = nullptr;


		//사운드
		Sound::Sound BGM;
		struct final
		{
			Sound::Sound Decide;
			Sound::Sound Move;
		}SE;
	}

	void Start()
	{
		using namespace ConstValue;
		SyncValue = 0;
		SpeedValue = DefSpeed;
		MappedKeys[0] = DefKeys[0];
		MappedKeys[1] = DefKeys[1];
		MappedKeys[2] = DefKeys[2];
		MappedKeys[3] = DefKeys[3];
		Volume = DefVolume;

		pCh = new Chart();

		BGMTitle = "TitleBGM";

		BGM.Content = BGMTitle.data();
		BGM.loop = true;
		BGM.volume = Volume;

		SE.Decide.Content = "SE_Decide";
		SE.Decide.loop = false;
		SE.Decide.volume = Volume;

		SE.Move.Content = "SE_Move";
		SE.Move.loop = false;
		SE.Move.volume = Volume;
	}

	void End() { delete pCh; }
	void PlayBGM() { BGM.Play(); }
	void PauseBGM() { BGM.Pause(); }
	void StopBGM() { BGM.Stop(); }
	void PlaySEDecide() { SE.Decide.Play(); }
	void PlaySEMove() { SE.Move.Play(); }

	namespace Get
	{
		int SyncValue() { return GameValue::SyncValue; }
		float SpeedValue() { return GameValue::SpeedValue; }
		void Keys(size_t (&target)[4]) { for (UINT u = 0; u < 4; u++) target[u] = GameValue::MappedKeys[u]; }
		const char* Title() { return BGMTitle.data(); }
		Chart *pChart() { return pCh; }
		float Volume() { return GameValue::Volume; }
	}
	namespace Set
	{
		void SyncValue(int const& newSync) { GameValue::SyncValue = newSync; }
		void SpeedValue(float const& newSpeed) { GameValue::SpeedValue = newSpeed; };
		void Keys(size_t (&newKeys)[4]) { for (UINT u = 0; u < 4; u++) GameValue::MappedKeys[u] = newKeys[u]; }
		void pChart(Chart* ch) { memcpy(pCh, ch, sizeof(Chart)); };
		void BGM(std::string const& title) { BGMTitle = title; }
		void Volume(float const& volume) 
		{ 
			GameValue::Volume = volume;
			GameValue:: BGM.volume = volume;
			SE.Decide.volume = volume; 
			SE.Move.volume = volume;
		}
	}
};