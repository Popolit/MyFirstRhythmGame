#include "stdafx.h"
#include "Result.h"

Result::Result()
{
	STR.Score = "";
	STR.MaxCombo = "";
	STR.Perfect = "";
	STR.Good = "";
	STR.Miss = "";

	Render.Score.Content = STR.Score.data();
	Render.Score.Location = { 1000, 250 };
	Render.Score.Length = { 500, 100 };
	Render.Score.Font = { "CookieRun Regular", 50, true };
	Render.Score.Color = { 255, 255, 255 };

	Render.MaxCombo.Content = STR.MaxCombo.data();
	Render.MaxCombo.Location = { 1000, 350 };
	Render.MaxCombo.Length = { 300, 100 };
	Render.MaxCombo.Font = { "CookieRun Regular", 30, true };
	Render.MaxCombo.Color = { 255, 255,255 };

	Render.Perfect.Content = STR.Perfect.data();
	Render.Perfect.Location = { 1000, 400 };
	Render.Perfect.Length = { 300, 50 };
	Render.Perfect.Font = { "CookieRun Regular", 30, true };
	Render.Perfect.Color = { 255, 255, 255 };

	Render.Good.Content = STR.Good.data();
	Render.Good.Location = { 1000, 450 };
	Render.Good.Length = { 300, 50 };
	Render.Good.Font = { "CookieRun Regular", 30, true };
	Render.Good.Color = { 255, 255, 255 };

	Render.Miss.Content = STR.Miss.data();
	Render.Miss.Location = { 1000, 500 };
	Render.Miss.Length = { 300, 50 };
	Render.Miss.Font = { "CookieRun Regular", 30, true };
	Render.Miss.Color = { 255, 255, 255 };
}

void Result::Set(class Score* pScore, Combo* pCombo)
{
	STR.Score = pScore->strScore;
	STR.MaxCombo = std::to_string(pCombo->GetMaxCombo());
	STR.Perfect = std::to_string(pScore->Count.Perfect);
	STR.Good = std::to_string(pScore->Count.Good);
	STR.Miss = std::to_string(pScore->TotalCount - pScore->Count.Perfect - pScore->Count.Good);
}

void Result::Draw()
{
	Render.Score.Draw();
	Render.MaxCombo.Draw();
	Render.Perfect.Draw();
	Render.Good.Draw();
	Render.Miss.Draw();
}

