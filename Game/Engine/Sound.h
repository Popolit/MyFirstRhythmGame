#pragma once
#include <windows.h>
#include <cassert>
#include <map>
#include <string>
#include <XAudio2.h>

namespace Sound
{
	class Sound final
	{
	public:
		void Set(bool isLoop = false, UINT32 loopBegin = 0);
		void Play();
		void Pause();
		void Stop();
		void SetVolume(float const& volume);
	public:
		char const* Content = nullptr;
		bool paused = false;
	};
}