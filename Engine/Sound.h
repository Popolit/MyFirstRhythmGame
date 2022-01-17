#pragma once
#include "Resource.h"

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
		void Play();
		void Pause();
		void Stop();
		void SetVolume();
		bool isLoopEnd();
	public:
		char const* Content = nullptr;
	public:
		float volume = 0.0f;
		bool pause = false;
		bool loop = false;
		UINT32 loopBegin = 0;
		UINT32 loopLength = 850000;
	};
}