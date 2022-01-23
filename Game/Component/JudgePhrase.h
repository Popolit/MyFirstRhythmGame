#pragma once
#include "Manager/Resource.h"
#include "Manager/ConstValue.h"

class JudgePhrase final
{
private:
	ConstValue::Judge judge;
	float SpeedValue;
	float renderingTime;
	bool isVisible;

	Rendering::Animation::Component Perfect;
	Rendering::Animation::Component Good;
	Rendering::Animation::Component Miss;
public:
	JudgePhrase();
	void setJudge(ConstValue::Judge judge);
	void Update(float const& location);
};

