#include "stdafx.h"
#include "JudgePhrase.h"

void JudgePhrase::Start()
{
	SpeedValue = GameValue::Get::SpeedValue();

	Perfect.Content = "Perfect";
	Perfect.Location = { -300, 0 };
	Perfect.Length = { 150, 50 };

	Good.Content = "Good";
	Good.Location = { -300, 0 };
	Good.Length = { 150, 50 };

	Miss.Content = "Miss";
	Miss.Location = { -300, 0 };
	Miss.Length = { 150, 50 };

	renderingTime = 0.0f;	
}

void JudgePhrase::setJudge(ConstValue::Judge judge) 
{
	renderingTime = 1.0f;

	this->judge = judge; 
}

void JudgePhrase::Update()
{
	Perfect.Location[1] += SpeedValue * 100 * Time::Get::Delta();
	Good.Location[1] += SpeedValue * 100 * Time::Get::Delta();
	Miss.Location[1] += SpeedValue * 100 * Time::Get::Delta();

	if (renderingTime <= 0) return;

	renderingTime -= Time::Get::Delta();

	
	switch (judge)
	{
		case ConstValue::Judge::Perfect:
		{
			Perfect.Draw();
			break;
		}
		case ConstValue::Judge::Good:
		{
			Good.Draw();
			break;
		}
		case ConstValue::Judge::Miss:
		{
			Miss.Draw();
			break;
		}
	}
}


void JudgePhrase::End() {}