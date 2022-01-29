#include "stdafx.h"
#include "Result.h"

Result::Result()
{
	Perfect = false;
	FullCombo = false;

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

Result::Result(std::string result) : Result()
{
	if (result == "") return;
	size_t pos = result.find_first_of(',');
	
	STR.Score = result.substr(0, pos);
	result.erase(0, pos + sizeof(char) * 2);
	pos = result.find_first_of(',');

	STR.MaxCombo = result.substr(0, pos);
	result.erase(0, pos + sizeof(char) * 2);
	pos = result.find_first_of(',');

	STR.Perfect = result.substr(0, pos);
	result.erase(0, pos + sizeof(char) * 2);
	pos = result.find_first_of(',');

	STR.Good = result.substr(0, pos);
	result.erase(0, pos + sizeof(char) * 2);
	pos = result.find_first_of(',');

	STR.Miss = result.substr(0, pos);
	result.erase(0, pos + sizeof(char) * 2);
	pos = result.find_first_of(',');

	Perfect = stoi(result.substr(0, pos));
	result.erase(0, pos + sizeof(char) * 2);
	pos = result.find_first_of(',');

	FullCombo = stoi(result.substr(0, pos));
}

std::string Result::GetScore()
{
	return STR.Score;
}

void Result::Set(class Score* pScore, Combo* pCombo)
{
	STR.Score = pScore->strScore;
	STR.MaxCombo = std::to_string(pCombo->GetMaxCombo());
	STR.Perfect = std::to_string(pScore->Count.Perfect);
	STR.Good = std::to_string(pScore->Count.Good);
	STR.Miss = std::to_string(pScore->TotalCount - pScore->Count.Perfect - pScore->Count.Good);
}

void Result::Update(std::string const& title, Result* newResult)
{
	if (newResult->STR.Score < STR.Score) return;

	memcpy(this, newResult, sizeof(Result));
	
	std::string path = "Datas/" + title + ".txt";
	FILE* pFile = nullptr;

	std::string original;

	fopen_s(&pFile, path.data(), "r");
	char buffer = fgetc(pFile);
	
	while (buffer != EOF)
	{
		original += buffer;
		buffer = fgetc(pFile);
	}

	fclose(pFile);


	std::string Diff = ConstValue::ToString(Resource::Get::Diff());

	size_t pos = original.find("\n[BestScore]");
	std::string others = original.substr(0, pos);


	original.erase(0, pos);

	std::string scores = "";
	pos = original.find("#Easy");
	if (pos != std::string::npos)
	{

	}
	pos = original.find("#" + Diff + ": ");


	/*highScore += "\n#" + Diff + ": ";
	highScore += STR.Score;
	highScore += ", " + STR.MaxCombo;
	highScore += ", " + STR.Perfect;
	highScore += ", " + STR.Good;
	highScore += ", " + STR.Miss;
	highScore += ", " + Perfect ? "1" : "0";
	highScore += ", " + FullCombo ? "1" : "0";*/

	//fopen_s(&pFile, path.data(), "w");
	//fputs((original + highScore).data(), pFile);

}


void Result::Draw()
{
	Render.Score.Draw();
	Render.MaxCombo.Draw();
	Render.Perfect.Draw();
	Render.Good.Draw();
	Render.Miss.Draw();
}

