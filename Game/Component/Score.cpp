#include "stdafx.h"
#include "Score.h"

Score::Score()
{
	digit = 0;
	strScore = "";
	for (UINT u = ConstValue::MaxScore; 0 < u; u /= 10)
	{
		digit++;
		strScore += '0';
	}
	TotalCount = 1;
	GainedScoreCount = 0.0f;

	CurrentScore.Content = strScore.data();
	CurrentScore.Length = { 200, 50 };
	CurrentScore.Location = { 1200, 30 };
	CurrentScore.Font = { "CookieRun Bold", 40, true };
	CurrentScore.Color = { 255, 255, 255 };
}

Score::Score(UINT const& count) : Score()
{
	if(count != 0) TotalCount = count;
}

Score::~Score()
{
	CurrentScore.Content = nullptr;
}

void Score::Update(ConstValue::Judge const& judge)
{
	if (judge == ConstValue::Judge::Perfect) GainedScoreCount += 1.0f;
	else if (judge == ConstValue::Judge::Good) GainedScoreCount += 0.5f;
	else return;

	strScore = "";
	UINT CalculatedScore = static_cast<UINT>(ConstValue::MaxScore * GainedScoreCount / TotalCount);
	for (UINT u = static_cast<UINT>(pow(10, digit - 1)); 0 < u; u /= 10)
	{
		strScore += '0' + ((CalculatedScore / u) % 10);
	}
}

void Score::DrawScore() 
{
	CurrentScore.Draw();
}
