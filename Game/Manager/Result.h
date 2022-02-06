#pragma once
#include "Component/Score.h"
#include "Component/Combo.h"

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
	std::string const& GetScore();
	bool IsFC();
	void Set(class Score *pScore, Combo* pCombo);
	void Update(std::string const& title, Result *newResult);
	ConstValue::Rank GetRank();
};