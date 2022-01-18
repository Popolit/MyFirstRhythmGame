#pragma once
#include"ConstValue.h"

class Chart;

namespace GameValue
{
	void Start();
	void PlaySE();

	namespace Get
	{
		int SyncValue();
		float SpeedValue();
		void Keys(size_t(&target)[4]);
		const char* Title();
		Chart* pChart();
	}
	namespace Set
	{
		void SyncValue(int const &newSync);
		void SpeedValue(float const &newSpeed);
		void Keys(size_t (&newKeys)[4]);
		void Title(std::string const & title);
		void pChart(Chart* ch);
		void SetVolume(float const& volume);
	}
}