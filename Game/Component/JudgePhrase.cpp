#include "stdafx.h"
#include "JudgePhrase.h"

void JudgePhrase::Start()
{
	SpeedValue = Resource::Get::SpeedValue();

	Perfect.Content = "Perfect";
	Perfect.Location = { -290, 0 };
	Perfect.Length = { 300, 100 };
	Perfect.Duration = 0.1f;
	Perfect.Repeatable = false;

	Good.Content = "Good";
	Good.Location = { -290, 0 };
	Good.Length = { 300, 100 };
	Good.Duration = 0.1f;
	Good.Repeatable = false;

	Miss.Content = "Miss";
	Miss.Location = { -290, 0 };
	Miss.Length = { 300, 100 };
	Miss.Duration = 0.1f;
	Miss.Repeatable = false;

	renderingTime = 0.0f;	
}

void JudgePhrase::setJudge(ConstValue::Judge judge) 
{
	renderingTime = 1.0f;
	Perfect.Playback = 0.0f;
	Good.Playback = 0.0f;
	Miss.Playback = 0.0f;

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