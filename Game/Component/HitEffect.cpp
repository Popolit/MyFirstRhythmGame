#include "stdafx.h"
#include "HitEffect.h"

void HitEffect::Start()
{
	SpeedValue = Resource::Get::SpeedValue();
	duration = 0.0f;

	effect.Content = "HitEffect";
	effect.Location[1] = -248;
	effect.Length = { 100, 100 };
	effect.Duration = 0.3f;
	effect.Repeatable = true;
}

void HitEffect::reset() { duration = 0.3f;}

void HitEffect::setLane(UINT const &lane)
{
	effect.Location[0] = -450 + static_cast<float>(100 * lane);
}

void HitEffect::Update()
{
	effect.Location[1] += SpeedValue * 100 * Time::Get::Delta();
	if (duration <= 0) return;

	duration -= Time::Get::Delta();
	
	effect.Draw();
}


void HitEffect::End() {}