#include "stdafx.h"
#include "GameValue.h"
#include "Component/Chart.h"

namespace GameValue
{
	namespace
	{
		int SyncValue = int();
		float SpeedValue = float();
		size_t MappedKeys[4] = { 0, };
		std::string SongTitle;
		Chart* pCh = nullptr;
		Sound::Sound SE;
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
		pCh = new Chart();

		SE.Content = "SE";
		SE.loop = false;
		SE.volume = 0.1f;
	}

	void End() { delete pCh; }
	void PlaySE() { SE.Play(); }

	namespace Get
	{
		int SyncValue() { return GameValue::SyncValue; }
		float SpeedValue() { return GameValue::SpeedValue; }
		void Keys(size_t (&target)[4]) { for (UINT u = 0; u < 4; u++) target[u] = GameValue::MappedKeys[u]; }
		const char* Title() { return SongTitle.data(); }
		Chart *pChart() { return pCh; }
	}
	namespace Set
	{
		void SyncValue(int const& newSync) { GameValue::SyncValue = newSync; }
		void SpeedValue(float const& newSpeed) { GameValue::SpeedValue = newSpeed; };
		void Keys(size_t (&newKeys)[4]) { for (UINT u = 0; u < 4; u++) GameValue::MappedKeys[u] = newKeys[u]; }
		void Title(std::string const& title) { SongTitle = title; }
		void pChart(Chart* ch) { memcpy(pCh, ch, sizeof(Chart)); };
		void Volume(float const& volume) { SE.volume = volume; }
	}
};