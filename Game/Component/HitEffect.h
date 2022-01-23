#pragma once
#include "Manager/Resource.h"
class HitEffect final
{
private:
	float SpeedValue;
	float duration;
	Rendering::Animation::Component effect;
public:
	HitEffect();
	void Reset();
	void SetLane(UINT const& lane);
	void Update(float const& location);
};

