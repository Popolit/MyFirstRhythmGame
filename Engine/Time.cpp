#include "Time.h"

#include <Windows.h>
#include <chrono>

namespace Time
{
	namespace
	{
		//steady_clock : 로컬 시간
		//system_clock : 인터넷 시간
		std::chrono::steady_clock::time_point const Started = std::chrono::steady_clock::now();
		std::chrono::steady_clock::time_point		Updated = std::chrono::steady_clock::now();

		float Elapsed	   = float();	//게임 시작 후 지난 시간
		float Delta = float();
	}

	namespace Get
	{
		float Elapsed() { return Time::Elapsed; }
		float Delta()	{ return Time::Delta; }
	}

	void Procedure(HWND const hWindow, UINT const uMessage, WPARAM const wParameter, LPARAM const lParameter)
	{
		switch (uMessage)
		{

			case WM_APP:
			{
				using namespace std::chrono;
				Elapsed	 = duration_cast<duration<float>> (steady_clock::now() - Started).count();
				Delta	 = duration_cast<duration<float>> (steady_clock::now() - Updated).count();

				Updated = steady_clock::now();

				return;
			}
		}
	}
}