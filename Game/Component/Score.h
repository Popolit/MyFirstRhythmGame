#pragma once
#include "Manager/ConstValue.h"
#include "Manager/Resource.h"
#include <string>

//점수 클래스
class Score final
{
private:
	friend class Result;

	UINT Digit;		//점수 자릿수, 1000000 MaxScore 기준 7
	UINT TotalCount;
	float Coeff;	//계수, Perfect = 1.0, Good = 0.5

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
	void Draw();
};

