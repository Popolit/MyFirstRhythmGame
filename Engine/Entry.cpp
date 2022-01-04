// DirectX : GPU 기능을 사용할 수 있는 API

#pragma region CPU / GPU

// CPU : 입출력 , 기억 , 연산 , 제어 컴퓨터의 리소스를 처리해주는 중앙 처리 장치
//       직렬 연산 ( 순차적으로 연산 )
//       연산 처리속도가 매우 높음

// GPU : 그래픽 처리 장치 , 대량의 연산을 빠르게 할 수 있다는 장점을 가짐
//       렌더링 픽셀 하나하나에 대한 연산이 필요하므로 대량의 연산이 필요한데,
//       이러한 연산을 처리해주는 장치

#pragma endregion

#include <Windows.h>
using namespace std;

namespace Engine
{
	LRESULT CALLBACK Procedure(HWND const, UINT const, WPARAM const, LPARAM const);
}
int APIENTRY WinMain
(
	_In_ HINSTANCE const hInstance,
	_In_opt_ HINSTANCE const hPrevInstance,
	_In_ LPSTR const lpCmdLine,
	_In_ int const nShowCmd
)
{
	HWND hWindow = nullptr;

	{
		//윈도우 창의 클래스를 만들어주는 작업
		WNDCLASSEX wndClass = WNDCLASSEX();

		wndClass.cbSize        = sizeof(WNDCLASSEX);
		wndClass.lpfnWndProc   = Engine::Procedure;
		wndClass.hInstance     = hInstance;
		wndClass.hIcon         = LoadIcon(nullptr, IDI_APPLICATION);
		wndClass.hCursor       = LoadCursor(nullptr, IDC_ARROW);
		wndClass.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
		wndClass.lpszClassName = "Window";	//만들 클래스의 이름
		wndClass.hIconSm       = LoadIcon(nullptr, IDI_APPLICATION);

		RegisterClassEx(&wndClass);
	}


	{

		//위에서 만든 클래스에 대한 객체를 만듬
		CREATESTRUCT window = CREATESTRUCT();
		
		window.lpszClass = "Window";
		window.lpszName = "Game";
		window.style = WS_CAPTION | WS_SYSMENU;
		window.cx = 1280;
		window.cy = 720;
		window.hInstance = hInstance;

		//프로그램 창이 중앙에 뜨도록 지정
		{
			RECT rect = RECT();
			rect.right = window.cx;
			rect.bottom = window.cy;

			//윈도우 창을 옮김
			AdjustWindowRectEx(&rect, window.style, static_cast<bool>(window.hMenu), window.dwExStyle);

			window.cx = rect.right - rect.left;
			window.cy = rect.bottom - rect.top;

			window.x = (GetSystemMetrics(SM_CXSCREEN) - window.cx) / 2;
			window.y = (GetSystemMetrics(SM_CYSCREEN) - window.cy) / 2;
		}

		hWindow = CreateWindowEx
		(
			window.dwExStyle,
			window.lpszClass,
			window.lpszName,
			window.style,
			window.x,
			window.y,
			window.cx,
			window.cy,
			window.hwndParent,
			window.hMenu,
			window.hInstance,
			window.lpCreateParams
		);

		

		ShowWindow(hWindow, SW_RESTORE);
	}

	{
		//메시지를 담는 구조체
		MSG msg = MSG();
		while (true)
		{
			//GetMessage = 대기 타임이 존재함
			//PeekMessage = 메시지가 있으면 True, 없으면 False 반환
			if (PeekMessage(&msg, HWND(), WM_NULL, WM_NULL, PM_REMOVE))
			{
				//창의 X키와 다름
				if (msg.message == WM_QUIT) return static_cast<int>(msg.wParam);	//wParam == long타입

				//메시지 처리 함수로 전송
				DispatchMessage(&msg);
			}

			//WM_APP = 사용자 정의 메시지
			else SendMessage(hWindow, WM_APP, 0, 0);
		}
	}
}