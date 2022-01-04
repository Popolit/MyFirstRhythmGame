// DirectX : GPU ����� ����� �� �ִ� API

#pragma region CPU / GPU

// CPU : ����� , ��� , ���� , ���� ��ǻ���� ���ҽ��� ó�����ִ� �߾� ó�� ��ġ
//       ���� ���� ( ���������� ���� )
//       ���� ó���ӵ��� �ſ� ����

// GPU : �׷��� ó�� ��ġ , �뷮�� ������ ������ �� �� �ִٴ� ������ ����
//       ������ �ȼ� �ϳ��ϳ��� ���� ������ �ʿ��ϹǷ� �뷮�� ������ �ʿ��ѵ�,
//       �̷��� ������ ó�����ִ� ��ġ

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
		//������ â�� Ŭ������ ������ִ� �۾�
		WNDCLASSEX wndClass = WNDCLASSEX();

		wndClass.cbSize        = sizeof(WNDCLASSEX);
		wndClass.lpfnWndProc   = Engine::Procedure;
		wndClass.hInstance     = hInstance;
		wndClass.hIcon         = LoadIcon(nullptr, IDI_APPLICATION);
		wndClass.hCursor       = LoadCursor(nullptr, IDC_ARROW);
		wndClass.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
		wndClass.lpszClassName = "Window";	//���� Ŭ������ �̸�
		wndClass.hIconSm       = LoadIcon(nullptr, IDI_APPLICATION);

		RegisterClassEx(&wndClass);
	}


	{

		//������ ���� Ŭ������ ���� ��ü�� ����
		CREATESTRUCT window = CREATESTRUCT();
		
		window.lpszClass = "Window";
		window.lpszName = "Game";
		window.style = WS_CAPTION | WS_SYSMENU;
		window.cx = 1280;
		window.cy = 720;
		window.hInstance = hInstance;

		//���α׷� â�� �߾ӿ� �ߵ��� ����
		{
			RECT rect = RECT();
			rect.right = window.cx;
			rect.bottom = window.cy;

			//������ â�� �ű�
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
		//�޽����� ��� ����ü
		MSG msg = MSG();
		while (true)
		{
			//GetMessage = ��� Ÿ���� ������
			//PeekMessage = �޽����� ������ True, ������ False ��ȯ
			if (PeekMessage(&msg, HWND(), WM_NULL, WM_NULL, PM_REMOVE))
			{
				//â�� XŰ�� �ٸ�
				if (msg.message == WM_QUIT) return static_cast<int>(msg.wParam);	//wParam == longŸ��

				//�޽��� ó�� �Լ��� ����
				DispatchMessage(&msg);
			}

			//WM_APP = ����� ���� �޽���
			else SendMessage(hWindow, WM_APP, 0, 0);
		}
	}
}