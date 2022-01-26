#include "stdafx.h"
#include "HitEffect.h"

HitEffect::HitEffect()
{
	SpeedValue = Resource::Get::SpeedValue();
	duration = 0.0f;

	effect.Content = "HitEffect";
	effect.Location[1] = -248;
	effect.Length = { 210, 210 };
	effect.Duration = 0.3f;
	effect.Repeatable = false;
	

	effectL.Content = "HitEffectL";
	effectL.Location[1] = -248;
	effectL.Length = { 210, 210 };
	effectL.Duration = 0.3f;
	effectL.Repeatable = true;
}

void HitEffect::Reset(bool const& isLong) 
{ 
	if (isLong) durationL = 0.2f;
	else
	{
		effect.Playback = 0;
		duration = 0.3f;
	}
}

void HitEffect::SetLane(UINT const &lane)
{
	effect.Location[0] = -450 + static_cast<float>(100 * lane);
	effectL.Location[0] = effect.Location[0];
}

void HitEffect::Update(float const& location)
{
	if (0 < duration)
	{
		effect.Location[1] = location - 248;
		effect.Draw();
	}
	else if (0 < durationL)
	{
		effectL.Location[1] = location - 248;
		effectL.Draw();
	}
	else return;

	duration -= Time::Get::Delta();
	durationL -= Time::Get::Delta();
}
