#pragma once
#include "Manager/Resource.h"

//히트 이펙트 클래스
class HitEffect final
{
private:
	float SpeedValue;
	float durationL;
	Rendering::Animation::Component effect;
	Rendering::Animation::Component effectL; //롱노트
public:
	HitEffect();
	void Update(bool const& isLong = false);
	void SetLane(UINT const& lane);
	void Draw(float const& location);
};

