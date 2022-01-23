#pragma once
#include "Manager/ConstValue.h"
#include "Manager/Resource.h"
#include <string>

class Score
{
private:
	UINT Digit;
	UINT TotalCount;
	float Coeff;	//°è¼ö, Perfect = 1.0, Good = 0.5

	struct
	{
		UINT Perfect;
		UINT Good;
	}Count;

	std::string strScore;

	Rendering::Text::Component CurrentScore;
public:
	Score();
	Score(UINT const &count);
	~Score();
	void Update(ConstValue::Judge const & judge);
	void DrawScore();
};

