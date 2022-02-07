#pragma once
#include "Manager/ConstValue.h"
#include "Manager/Resource.h"
#include <string>

//���� Ŭ����
class Score final
{
private:
	friend class Result;

	UINT Digit;		//���� �ڸ���, 1000000 MaxScore ���� 7
	UINT TotalCount;
	float Coeff;	//���, Perfect = 1.0, Good = 0.5

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

