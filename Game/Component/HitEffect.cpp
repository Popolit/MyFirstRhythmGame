#include "stdafx.h"
#include "HitEffect.h"

HitEffect::HitEffect()
{
	SpeedValue = Resource::Get::SpeedValue();
	duration = 0.0f;

	effect.Content = "HitEffect";
	effect.Location[1] = -248;
	effect.Length = { 100, 100 };
	effect.Duration = 0.3f;
	effect.Repeatable = true;
}

void HitEffect::Reset() { duration = 0.3f;}

void HitEffect::SetLane(UINT const &lane)
{
	effect.Location[0] = -450 + static_cast<float>(100 * lane);
}

void HitEffect::Update(float const& location)
{
	effect.Location[1] = location - 248;
	if (duration <= 0) return;

	duration -= Time::Get::Delta();
	
	effect.Draw();
}
