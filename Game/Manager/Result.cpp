#include "stdafx.h"
#include "Result.h"
#include <regex>

//���� ��������� ���� ����� ������
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

//���� ����� ���� ����� ������
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

//���� �� ������ ���� ��ũ�� �ű�� �Լ�
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

//�÷��� �� �� Result�� ����� Set
void Result::Set(class Score* pScore, Combo* pCombo)
{
	STR.Score = pScore->strScore;
	STR.MaxCombo = std::to_string(pCombo->GetMaxCombo());
	STR.Perfect = std::to_string(pScore->Count.Perfect);
	STR.Good = std::to_string(pScore->Count.Good);
	STR.Miss = std::to_string(pScore->TotalCount - pScore->Count.Perfect - pScore->Count.Good);
	SetRank();
}

//�ְ� ����� �����ų�, ��ũ�� ���ŵǸ� ����
void Result::Update(std::string const& title, Result* newResult)
{
	//������ ������ ����
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
	//���� ���ھ ����
	if (pos != std::string::npos) scores = original.substr(pos);
	//���ھ ������ ���� ���� ����
	else scores = "\n\n[BestScore]\n#Easy: \n#Normal: \n#Hard: ";

	//���� ��ü�� ���ھ�
	std::string newScore;

	newScore += "#" + Diff + ": ";
	newScore += STR.Score;
	newScore += ", " + STR.MaxCombo;
	newScore += ", " + STR.Perfect;
	newScore += ", " + STR.Good;
	newScore += ", " + STR.Miss;
	newScore += ", " + std::to_string(Perfect);
	newScore += ", " + std::to_string(FullCombo);

	//���ھ� ��ü
	scores = std::regex_replace(scores, std::regex("^#" + Diff + "[^\n]*"), newScore);

	//���� ���� �� ����
	fopen_s(&pFile, path.data(), "w");
	fputs((others + scores).data(), pFile);
	fclose(pFile);
}

ConstValue::Rank Result::GetRank()
{
	return Rank;
}
