#pragma once
#include "Component/Score.h"
#include "Component/Combo.h"

class Result final
{
private:
	friend class ResultScene;

	bool Perfect;
	bool FullCombo;

	struct
	{
		std::string Perfect;
		std::string Good;
		std::string Miss;
		std::string Score;
		std::string MaxCombo;
	}STR;
	struct
	{
		Rendering::Text::Component Perfect;
		Rendering::Text::Component Good;
		Rendering::Text::Component Miss;
		Rendering::Text::Component Score;
		Rendering::Text::Component MaxCombo;
	}Render;

public:
	Result();
	Result(std::string result);
	std::string GetScore();
	bool IsFC();
	void Set(class Score *pScore, Combo* pCombo);
	void Update(std::string const& title, Result *newResult);
	void Draw();
};