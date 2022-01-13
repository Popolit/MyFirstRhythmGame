#include "Sound.h"

#if not defined _DEBUG
#define MUST(Expression) (      (         (Expression)))
#else
#define MUST(Expression) (assert(SUCCEEDED(Expression)))
#endif

#ifdef _XBOX	//Big-Endian
#define fourccRIFF 'RIFF'
#define fourccDATA 'data'
#define fourccFMT 'fmt '
#define fourccWAVE 'WAVE'
#define fourccXWMA 'XWMA'
#define fourccDPDS 'dpds'
#endif

#ifndef _XBOX //Little-Endian
#define fourccRIFF 'FFIR'
#define fourccDATA 'atad'
#define fourccFMT ' tmf'
#define fourccWAVE 'EVAW'
#define fourccXWMA 'AMWX'
#define fourccDPDS 'sdpd'
#endif
	
namespace Sound
{
	namespace
	{
		IXAudio2* XAudio2 = nullptr;	//XAudio 엔진 디바이스
		IXAudio2MasteringVoice* MasterVoice = nullptr;	//오디오 캡슐화 오디오 그래프를 통과하는 모든 오디오의 최종대상

		WAVEFORMATEXTENSIBLE wfx = { 0 };	//WAVE 형식을 저장함
		XAUDIO2_BUFFER buffer = { 0 };

		IXAudio2SourceVoice* SourceVoice;
	}

	//오디오 찾기
	HRESULT FindAudio(HANDLE hAudio, DWORD fourcc, DWORD &dwAudioSize, DWORD &dwAudioDataPosition)
	{
		HRESULT hr = S_OK;
		if (INVALID_SET_FILE_POINTER == SetFilePointer(hAudio, 0, NULL, FILE_BEGIN)) 
			return HRESULT_FROM_WIN32(GetLastError());

		DWORD dwAudioType;
		DWORD dwAudioDataSize;
		DWORD dwRIFFDataSize = 0;
		DWORD dwFileType;
		DWORD bytesRead = 0;
		DWORD dwOffset = 0;

		while (hr == S_OK)
		{
			DWORD dwRead;
			if(0 == ReadFile(hAudio, &dwAudioType, sizeof(DWORD), &dwRead, NULL))
				hr = HRESULT_FROM_WIN32(GetLastError());

			if(0 == ReadFile(hAudio, &dwAudioDataSize, sizeof(DWORD), &dwRead, NULL))
				hr = HRESULT_FROM_WIN32(GetLastError());
			
			if (dwAudioType == fourccRIFF)
			{
				dwRIFFDataSize = dwAudioDataSize;
				dwAudioDataSize = 4;
				if(0 == ReadFile(hAudio, &dwFileType, sizeof(DWORD), &dwRead, NULL))
					hr = HRESULT_FROM_WIN32(GetLastError());
			}
			else
			{
				if(INVALID_SET_FILE_POINTER == SetFilePointer(hAudio, dwAudioDataSize, NULL, FILE_CURRENT))
					return HRESULT_FROM_WIN32(GetLastError());
			}

			dwOffset += sizeof(DWORD) * 2;
			if (dwAudioType == fourcc)
			{
				dwAudioSize = dwAudioDataSize;
				dwAudioDataPosition = dwOffset;
				return S_OK;
			}

			dwOffset += dwAudioDataSize;
			if (bytesRead >= dwRIFFDataSize) return S_FALSE;
		}

		return S_OK;
	}

	HRESULT ReadAudioData(HANDLE hFile, void* buffer, DWORD bufferSize, DWORD bufferOffset)
	{
		HRESULT hr = S_OK;
		if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, bufferOffset, NULL, FILE_BEGIN))
			return HRESULT_FROM_WIN32(GetLastError());
		DWORD dwRead;
		if (0 == ReadFile(hFile, buffer, bufferSize, &dwRead, NULL))
			hr = HRESULT_FROM_WIN32(GetLastError());

		return hr;
	}

	std::map<std::string, IXAudio2SourceVoice*> Storage;

	void Import(std::string const & file)
	{
		HANDLE hFile = CreateFile(
			file.c_str(),
			GENERIC_READ,
			FILE_SHARE_READ,
			NULL,
			OPEN_EXISTING,
			0,
			NULL
		);

		if (INVALID_HANDLE_VALUE == hFile) return;

		if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, 0, NULL, FILE_BEGIN)) return;

		DWORD dwAudioSize;
		DWORD dwAudioPosition;
		MUST(FindAudio(hFile, fourccRIFF, dwAudioSize, dwAudioPosition));
		DWORD fileType;
		MUST(ReadAudioData(hFile, &fileType, sizeof(DWORD), dwAudioPosition));
		if (fileType != fourccWAVE) return;

		MUST(FindAudio(hFile, fourccFMT, dwAudioSize, dwAudioPosition));
		MUST(ReadAudioData(hFile, &wfx, dwAudioSize, dwAudioPosition));

		MUST(FindAudio(hFile, fourccDATA, dwAudioSize, dwAudioPosition));
		BYTE* pDataBuffer = new BYTE[dwAudioSize];
		MUST(ReadAudioData(hFile, pDataBuffer, dwAudioSize, dwAudioPosition));

		buffer.AudioBytes = dwAudioSize;
		buffer.pAudioData = pDataBuffer;
		buffer.Flags = XAUDIO2_END_OF_STREAM;

		MUST(XAudio2->CreateSourceVoice(&SourceVoice, (WAVEFORMATEX*)&wfx));
		MUST(SourceVoice->SubmitSourceBuffer(&buffer));

		{
			size_t const x = file.find_first_of('/') + sizeof(char);
			size_t const y = file.find_last_of('.');

			Storage.try_emplace(file.substr(x, y - x), SourceVoice);
		}
		return;
	}

	void Procedure(HWND const hWindow, UINT const uMessage, WPARAM const wParameter, LPARAM const lParameter)
	{

		switch (uMessage)
		{
			case WM_CREATE:
			{
				MUST(CoInitializeEx(nullptr, COINITBASE_MULTITHREADED));		//COM 초기화 확인
				MUST(XAudio2Create(&XAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR));	//XAudio 인스턴스 생성
				MUST(XAudio2->CreateMasteringVoice(&MasterVoice));				//MasteringVoice 생성

				Resource::Import("Sound", Import);
				return;
			}
			case WM_DESTROY: {return; }
		}
	}

	void Sound::Play()
	{
		IXAudio2SourceVoice* const& sound = Storage.at(Content);
		MUST(sound->SetVolume(volume));
		MUST(sound->Start());
	}

	/*
	void Sound::SamplePlay(UINT32 const & Playbegin, UINT32 const & Length)
	{
		buffer = {  
		UINT32     Flags;
		UINT32     AudioBytes;
		const BYTE *pAudioData;
		UINT32     PlayBegin;
		UINT32     PlayLength;
		UINT32     LoopBegin;
		UINT32     LoopLength;
		UINT32     LoopCount;
		void       *pContext;
	}
	*/
	void Sound::Pause()
	{
		IXAudio2SourceVoice* const& sound = Storage.at(Content);
		MUST(sound->Stop());
	}

	void Sound::Stop()
	{
		IXAudio2SourceVoice* const& sound = Storage.at(Content);
		MUST(sound->Stop());
		MUST(sound->FlushSourceBuffers());
		//MUST(sound->SubmitSourceBuffer(new XAUDIO2_BUFFER, new XAUDIO2_BUFFER_WMA));
	}
}