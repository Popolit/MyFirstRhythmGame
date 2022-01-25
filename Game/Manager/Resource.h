#pragma once
#include"ConstValue.h"
#include "SoundManager.h"

class Chart;
class Song;
class Score;
class Combo;
class Result;

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
		int SongIndex();
		ConstValue::Difficulty Diff();
		Result* NowResult();
	}
	namespace Set
	{
		void SyncValue(int const &newSync);
		void SpeedValue(float const &newSpeed);
		void Keys(size_t (&newKeys)[4]);
		void NowPlaying(int& index);
		void Diff(ConstValue::Difficulty const &diff);
		void NowResult(Score* score, Combo* combo);
	}
}