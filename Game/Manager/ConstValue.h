#pragma once

namespace ConstValue
{
	const UINT JudgeRange = 33;	//ms
	const UINT MissRange = 200; //ms
	const UINT recognizeRange = 1000; //ms;
	enum Judge { Perfect, Good, Miss, None };
	enum SceneList { Main, Selection, Option, Play };
}