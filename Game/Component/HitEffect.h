#pragma once
#include "Manager/Resource.h"
class HitEffect final
{
private:
	float SpeedValue;
	float duration;
	float durationL;
	Rendering::Animation::Component effect;
	Rendering::Animation::Component effectL; //∑’≥Î∆Æ
public:
	HitEffect();
	void Reset(bool const& isLong = false);
	void SetLane(UINT const& lane);
	void Update(float const& location);
};

