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
		void Play();
		void Pause();
		void Stop();

	public:
		char const* Content = nullptr;

	public:
		float volume = 0;
		bool loop = false;
	};
}