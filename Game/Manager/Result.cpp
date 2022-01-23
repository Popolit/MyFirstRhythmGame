#include "stdafx.h"
#include "Result.h"

Result::Result()
{
	Score = 0;
	MaxCombo = 0;

	Count.Perfect = 0;
	Count.Good = 0;
	Count.Miss = 0;
}

void Result::Set(class Score* pScore, Combo* pCombo)
{
	//Score = pScore;
}

