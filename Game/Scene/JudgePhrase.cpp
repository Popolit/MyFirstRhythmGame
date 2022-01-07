#include "stdafx.h"
#include "JudgePhrase.h"

void JudgePhrase::Start()
{
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

UINT JudgePhrase::Update()
{
	renderingTime -= Time::Get::Delta();

	Perfect.Location[1] += 500 * Time::Get::Delta();
	Good.Location[1] += 500 * Time::Get::Delta();
	Miss.Location[1] += 500 * Time::Get::Delta();


	if (renderingTime <= 0)
	{
		renderingTime = 0;
		return 0;
	}

	switch (judge)
	{
		case ConstValue::Perfect:
		{
			Perfect.Draw();
			break;
		}
		case ConstValue::Good:
		{
			Good.Draw();
			break;
		}
		case ConstValue::Miss:
		{
			Miss.Draw();
			break;
		}
	}
	return 0;
}


void JudgePhrase::End() {}