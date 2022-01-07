#pragma once
#include "Manager/ConstValue.h"
#include "Manager/Scene.h"


class JudgePhrase final : public Scene
{
private:
	ConstValue::Judge judge;
	float renderingTime;
	bool isVisible;

	Rendering::Image::Component Perfect;
	Rendering::Image::Component Good;
	Rendering::Image::Component Miss;
public:
	void Start() override;
	void setJudge(ConstValue::Judge judge);
	UINT Update() override;
	void End() override;
};

