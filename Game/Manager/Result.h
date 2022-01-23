#pragma once
#include "Component/Score.h"
#include "Component/Combo.h"
class Result
{
private:
	UINT Score;
	UINT MaxCombo;
	struct 
	{
		UINT Perfect;
		UINT Good;
		UINT Miss;
	}Count;
public:
	Result();
	void Set(class Score *pScore, Combo* pCombo);
};