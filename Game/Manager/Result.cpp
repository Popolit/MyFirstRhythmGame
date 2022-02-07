#include "stdafx.h"
#include "Result.h"
#include <regex>

//기존 유저기록이 없을 경우의 생성자
Result::Result()
{
	Perfect = false;
	FullCombo = false;
	Score = 0;
	Rank = ConstValue::Rank::None;

	STR.Score = "";
	STR.MaxCombo = "";
	STR.Perfect = "";
	STR.Good = "";
	STR.Miss = "";
}

//유저 기록이 있을 경우의 생성자
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
	SetRank();
}

//점수 및 성적에 따라 랭크를 매기는 함수
void Result::SetRank()
{
	using namespace ConstValue;
	if (STR.Score == "") return; 
	if (Perfect) { Rank = Rank::P; return; }
	if (FullCombo) { Rank = Rank::FC; return; }

	UINT score = std::stoi(STR.Score);
	if (RankToScore.at(Rank::S) <= score) { Rank = Rank::S; return; }
	if (RankToScore.at(Rank::A) <= score) { Rank = Rank::A; return; }
	if (RankToScore.at(Rank::B) <= score) { Rank = Rank::B; return; }
	if (RankToScore.at(Rank::C) <= score) { Rank = Rank::C; return; }
	Rank = Rank::D;
}

std::string const & Result::GetScore()
{
	return STR.Score;
}

bool Result::IsFC()
{
	return FullCombo;
}

//플레이 후 새 Result가 생기면 Set
void Result::Set(class Score* pScore, Combo* pCombo)
{
	STR.Score = pScore->strScore;
	STR.MaxCombo = std::to_string(pCombo->GetMaxCombo());
	STR.Perfect = std::to_string(pScore->Count.Perfect);
	STR.Good = std::to_string(pScore->Count.Good);
	STR.Miss = std::to_string(pScore->TotalCount - pScore->Count.Perfect - pScore->Count.Good);
	SetRank();
}

//최고 기록이 나오거나, 랭크가 갱신되면 갱신
void Result::Update(std::string const& title, Result* newResult)
{
	//점수와 별개로 갱신
	Perfect |= newResult->Perfect;
	FullCombo |= newResult->FullCombo;

	if (newResult->STR.Score < STR.Score) return;

	STR.Score = newResult->STR.Score;
	STR.MaxCombo = newResult->STR.MaxCombo;
	STR.Perfect = newResult->STR.Perfect;
	STR.Good = newResult->STR.Good;
	STR.Miss = newResult->STR.Miss;

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

	std::string Diff = ConstValue::DiffToStr.at(Resource::Get::Diff());

	size_t pos = original.find("\n\n[BestScore]");
	std::string others = original.substr(0, pos);
	std::string scores;
	//기존 스코어가 존재
	if (pos != std::string::npos) scores = original.substr(pos);
	//스코어가 없으면 새로 포맷 생성
	else scores = "\n\n[BestScore]\n#Easy: \n#Normal: \n#Hard: ";

	//새로 교체될 스코어
	std::string newScore;

	newScore += "#" + Diff + ": ";
	newScore += STR.Score;
	newScore += ", " + STR.MaxCombo;
	newScore += ", " + STR.Perfect;
	newScore += ", " + STR.Good;
	newScore += ", " + STR.Miss;
	newScore += ", " + std::to_string(Perfect);
	newScore += ", " + std::to_string(FullCombo);

	//스코어 교체
	scores = std::regex_replace(scores, std::regex("^#" + Diff + "[^\n]*"), newScore);

	//파일 쓰기 후 종료
	fopen_s(&pFile, path.data(), "w");
	fputs((others + scores).data(), pFile);
	fclose(pFile);
}

ConstValue::Rank Result::GetRank()
{
	return Rank;
}
