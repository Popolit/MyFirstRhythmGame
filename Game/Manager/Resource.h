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
		Song* NowPlaying();
		size_t SongCount();
		SoundManager* SM();
		ConstValue::Difficulty Diff();
	}
	namespace Set
	{
		void SyncValue(int const &newSync);
		void SpeedValue(float const &newSpeed);
		void Keys(size_t (&newKeys)[4]);
		void Volume(float const&volume);
		void NowPlaying(size_t& index);
		void Diff(ConstValue::Difficulty const &diff);
	}
}