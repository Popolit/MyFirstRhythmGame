#pragma once
#include "ConstValue.h"
#include "SoundManager.h"
#include "Parser.h"

class Chart;
class Song;
class Score;
class Combo;
class Result;

//게임 내에서 사용되는 자원들
namespace Resource
{
	void Start();
	void End();
	void GetSongs();
	void GetOption();
	void SaveOption();

	namespace Get
	{
		int SyncValue();
		float SpeedValue();
		void Keys(size_t(&target)[4]);
		Song* NowPlaying();
		int SongIndex();
		ConstValue::Difficulty Diff();
	}
	namespace Set
	{
		void SyncValue(int const &newSync);
		void SpeedValue(float const &newSpeed);
		void Keys(size_t (&newKeys)[4]);
		void NowPlaying(int& index);
		void Diff(ConstValue::Difficulty const &diff);

	}
}