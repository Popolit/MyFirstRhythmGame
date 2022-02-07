#pragma once
#include "Manager/Resource.h"
#include "Manager/ConstValue.h"

//���� ���� Ŭ����
class JudgePhrase final
{
private:
	ConstValue::Judge judge;
	float SpeedValue;
	float renderingTime;

	Rendering::Animation::Component Perfect;
	Rendering::Animation::Component Good;
	Rendering::Animation::Component Miss;
public:
	JudgePhrase();
	void Update(ConstValue::Judge judge);
	void Draw(float const& location);
};

