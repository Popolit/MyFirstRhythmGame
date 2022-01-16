#pragma once
namespace ConstValue
{
	const UINT MaxScore = 1000000;

	const int MaxSync = 10000;
	const int MinSync = -10000;

	const float MaxSpeed = 20.0f;
	const float DefSpeed = 6.0f;
	const float MinSpeed = 0.5f;

	const UINT JudgeRange = 50;	//ms
	const UINT MissRange = 200; //ms
	const UINT recognizeRange = 1000; //ms;

	const size_t DefKeys[4] = { 0x44, 0x46, 0x4A, 0x4B };

	enum class Judge { Perfect, Good, Miss, None };
	enum class SceneList { Title, Play, SelectSong, Option, End  };
	enum class OptionList { Sync, Speed, Keys };
	enum class Difficulty { Easy, Normal, Hard };

    SceneList operator++(SceneList& sl);
    SceneList operator--(SceneList& sl);
    bool operator<(SceneList& A, SceneList& B);

    OptionList operator++(OptionList& ol);
    OptionList operator--(OptionList& ol);
	bool operator<(OptionList& A, OptionList& B);


	Difficulty operator++(Difficulty& d);
	Difficulty operator--(Difficulty& d);
	bool operator<(Difficulty& A, Difficulty& B);
}