#pragma once
#include"ConstValue.h"

class Chart;

namespace GameValue
{
	void Start();
	namespace Get
	{
		int SyncValue();
		float SpeedValue();
		void Keys(size_t(&target)[4]);
		Chart* pChart();
	}
	namespace Set
	{
		void SyncValue(int const &newSync);
		void SpeedValue(float const &newSpeed);
		void Keys(size_t (&newKeys)[4]);
		void pChart(Chart* ch);
	}
}