#pragma once
#include "Manager/GameValue.h"
#include "Manager/Scene.h"
class HitEffect final : public Scene
{
private:
	float SpeedValue;
	float duration;
	Rendering::Animation::Component effect;
public:
	void Start() override;
	void reset();
	void setLane(UINT const& lane);
	void Update() override;
	void End() override;
};

