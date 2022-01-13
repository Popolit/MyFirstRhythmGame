#pragma once
#include "Manager/ConstValue.h"
#include "Manager/GameValue.h"
#include <string>

class Score
{
private:
	UINT digit;
	UINT TotalCount;
	float GainedScoreCount;

	std::string strScore;

	Rendering::Text::Component CurrentScore;
public:
	Score();
	Score(UINT const &count);
	~Score();
	void Update(ConstValue::Judge const & judge);
	void DrawScore();
};

