#include <windows.h>
#include <cassert>
#include <XAudio2.h>

#if not defined _DEBUG
#define MUST(Expression) (      (         (Expression)))
#else
#define MUST(Expression) (assert(SUCCEEDED(Expression)))
#endif

#ifndef _XBOX
#define fourccRIFF 'FFIR'
#define fourccDATA 'atad'
#define fourccFMT 'tmf'
#define fourccWAVE 'EVAW'
#define fourccDPDS 'sdpd'
const char* strFileName = "";
#endif
	
namespace Sound
{
	namespace
	{
		IXAudio2* XAudio2 = nullptr;	//XAudio ���� ����̽�
		IXAudio2MasteringVoice* MasterVoice = nullptr;	//����� ĸ��ȭ ����� �׷����� ����ϴ� ��� ������� �������
	}
	void Procedure(HWND const hWindow, UINT const uMessage, WPARAM const wParameter, LPARAM const lParameter)
	{

		switch (uMessage)
		{
			case WM_CREATE:
			{
				MUST(CoInitializeEx(nullptr, COINITBASE_MULTITHREADED));		//COM �ʱ�ȭ Ȯ��
				MUST(XAudio2Create(&XAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR));	//XAudio �ν��Ͻ� ����
				MUST(XAudio2->CreateMasteringVoice(&MasterVoice));				//MasteringVoice ����

				/*HANDLE hFile = CreateFile(
					strFileName,
					GENERIC_READ,
					FILE_SHARE_READ,
					NULL,
					OPEN_EXISTING,
					0,
					NULL
				);*/

				return;
			}
			case WM_APP:
			{
				return;
			}
			case WM_SIZE:
			{
				return;
			}
			case WM_DESTROY:
			{
				PostQuitMessage(0);

				return;
			}
		}
	}
}