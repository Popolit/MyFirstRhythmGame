#pragma once
#include"ConstValue.h"

class Chart;

namespace GameValue
{
	void Start();
	void PlayBGM();
	void PauseBGM();
	void StopBGM();
	void PlaySEDecide();
	void PlaySEMove();

	namespace Get
	{
		int SyncValue();
		float SpeedValue();
		void Keys(size_t(&target)[4]);
		const char* Title();
		Chart* pChart();
		float Volume();
	}
	namespace Set
	{
		void SyncValue(int const &newSync);
		void SpeedValue(float const &newSpeed);
		void Keys(size_t (&newKeys)[4]);	
		void pChart(Chart* ch);
		void BGM(std::string const& title);
		void Volume(float const& volume);
	}
}