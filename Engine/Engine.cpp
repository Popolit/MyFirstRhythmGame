#include <Windows.h>
#include "Game.h"

//그려주는 역할
namespace Rendering
{
	void Procedure(HWND const, UINT const, WPARAM const, LPARAM const);
}
namespace Input
{
	void Procedure(HWND const, UINT const, WPARAM const, LPARAM const);
}
namespace Time
{
	void Procedure(HWND const, UINT const, WPARAM const, LPARAM const);
}
//값을 변경 (데미지 등)의 역할
namespace Engine
{
	namespace { Game* Portfolio; }
	LRESULT Procedure(HWND const hWindow, UINT const uMessage, WPARAM const wParameter, LPARAM const lParameter)
	{
		switch (uMessage)
		{
			case WM_CREATE:
			{
				Rendering::Procedure(hWindow, uMessage, wParameter, lParameter);

				(Portfolio = Initialize())->Start();

				return 0;
			}
			case WM_APP:
			{
				if(Portfolio->Update()) CloseWindow(hWindow);	
				Input::Procedure(hWindow, uMessage, wParameter, lParameter);
				Rendering::Procedure(hWindow, uMessage, wParameter, lParameter);
				Time::Procedure(hWindow, uMessage, wParameter, lParameter);
				return 0;
			}
			//Syskey == alt
			case WM_MOUSEWHEEL	: case WM_MOUSEHWHEEL	: case WM_MOUSEMOVE	:
			case WM_SYSKEYDOWN	: case WM_LBUTTONDOWN	: case WM_LBUTTONUP	:
			case WM_SYSKEYUP	: case WM_RBUTTONDOWN	: case WM_RBUTTONUP	:
			case WM_KEYDOWN		: case WM_MBUTTONDOWN	: case WM_MBUTTONUP	:
			case WM_KEYUP		: case WM_XBUTTONDOWN	: case WM_XBUTTONUP :
			{
				Input::Procedure(hWindow, uMessage, wParameter, lParameter);
				return 0;
			}
			case WM_SIZE:
			{
				Rendering::Procedure(hWindow, uMessage, wParameter, lParameter);

				return 0;
			}
			case WM_DESTROY:
			{
				Portfolio->End();
				delete Portfolio;

				Rendering::Procedure(hWindow, uMessage, wParameter, lParameter);
				PostQuitMessage(0);
				return 0;
			}
			default:
			{
				return DefWindowProc(hWindow, uMessage, wParameter, lParameter);
			}
		}
	}
}
