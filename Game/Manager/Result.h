#pragma once
#include "Component/Score.h"
#include "Component/Combo.h"

//게임 결과 정보를 저장하는 클래스
class Result final
{
private:
	friend class ResultScene;

	bool Perfect;
	bool FullCombo;
	UINT Score;
	ConstValue::Rank Rank;
	
	struct
	{
		std::string Perfect;
		std::string Good;
		std::string Miss;
		std::string Score;
		std::string MaxCombo;
	}STR;

private:
	void SetRank();
public:
	Result();
	Result(std::string result);
	Result(class Score *pScore, Combo* pCombo);
	void Update(std::string const& title, Result *newResult);
	std::string const& GetScore();
	bool IsFC();
	ConstValue::Rank GetRank();
};