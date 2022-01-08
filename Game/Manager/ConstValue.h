#pragma once

namespace ConstValue
{
	const UINT JudgeRange = 33;	//ms
	const UINT MissRange = 200; //ms
	const UINT recognizeRange = 1000; //ms;
	enum class Judge { Perfect, Good, Miss, None };
	enum class SceneList { Title, Play, SelectSong, Option, End  };
}