#include "stdafx.h"
#include "Keybeam.h"

Keybeam::Keybeam()
{
	KB.Content = "Keybeam";
	KB.Duration = 0.2f;
	KB.Length = { 100, 300 };
	KB.Repeatable = false;
	KB.Playback = 0.2f;
}

void Keybeam::SetLane(UINT const & lane)
{
	KB.Location[0] = -450 + static_cast<float>(100 * lane);
}

void Keybeam::Reset()
{
	KB.Playback = 0;
}

void Keybeam::Pressing()
{
	if(0.1f < KB.Playback) KB.Playback = 0.1f;
}

void Keybeam::Draw(float const& location)
{
	KB.Location[1] = location- 100;
	KB.Draw();
}