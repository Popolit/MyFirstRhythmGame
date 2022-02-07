#pragma once
#include "Manager/Resource.h"

//��Ʈ ����Ʈ Ŭ����
class HitEffect final
{
private:
	float SpeedValue;
	float durationL;
	Rendering::Animation::Component effect;
	Rendering::Animation::Component effectL; //�ճ�Ʈ
public:
	HitEffect();
	void Update(bool const& isLong = false);
	void SetLane(UINT const& lane);
	void Draw(float const& location);
};

