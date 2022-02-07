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

//레인 설정 함수
void Keybeam::SetLane(UINT const & lane)
{
	KB.Location[0] = -450 + static_cast<float>(100 * lane);
}

//키를 누르면 업데이트
void Keybeam::Update()
{
	KB.Playback = 0;
}

//누르고 있을 경우 키빔의 애니메이션을 고정
void Keybeam::Pressing()
{
	if(0.1f < KB.Playback) KB.Playback = 0.1f;
}

//키빔을 그려주는 함수
void Keybeam::Draw(float const& location)
{
	KB.Location[1] = location- 100;
	KB.Draw();
}