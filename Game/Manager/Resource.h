#pragma once
#include"ConstValue.h"
#include "SoundManager.h"

class Chart;
class Song;
namespace Resource
{
	void Start();
	void GetSongs();

	namespace Get
	{
		int SyncValue();
		float SpeedValue();
		void Keys(size_t(&target)[4]);
		const char* Title();
		Song* SongAt(size_t& index);
		Chart* pChart();
		SoundManager* SM();
	}
	namespace Set
	{
		void SyncValue(int const &newSync);
		void SpeedValue(float const &newSpeed);
		void Keys(size_t (&newKeys)[4]);	
		void pChart(Chart* ch);
		void Volume(float const&volume);
	}
}