#pragma once

namespace ConstValue
{
	const int MaxSync = 10000;
	const int MinSync = -10000;

	const float MaxSpeed = 12.0f;
	const float MinSpeed = 0.5f;

	const UINT JudgeRange = 33;	//ms
	const UINT MissRange = 200; //ms
	const UINT recognizeRange = 1000; //ms;
	enum class Judge { Perfect, Good, Miss, None };
	enum class SceneList { Title, Play, SelectSong, Option, End  };
	enum class OptionList { Sync, Speed, Keys };

    SceneList operator++(SceneList& sl);
    SceneList operator--(SceneList& sl);
    bool operator<(SceneList& A, SceneList& B);

    OptionList operator++(OptionList& ol);
    OptionList operator--(OptionList& ol);
	bool operator<(OptionList& A, OptionList& B);
}