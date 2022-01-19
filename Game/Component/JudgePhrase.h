#pragma once
#include "Manager/GameValue.h"
#include "Manager/ConstValue.h"
#include "Manager/Scene.h"


class JudgePhrase final : public Scene
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
	void Start() override;
	void setJudge(ConstValue::Judge judge);
	void Update() override;
	void End() override;
};

