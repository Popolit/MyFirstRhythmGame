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

	std::map<std::string, std::pair<IXAudio2SourceVoice*, XAUDIO2_BUFFER>> Storage;

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

		XAUDIO2_BUFFER buffer = { 0 };

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

		{
			size_t const x = file.find_first_of('/') + sizeof(char);
			size_t const y = file.find_last_of('.');

			Storage.try_emplace(file.substr(x, y - x), std::make_pair(SourceVoice, buffer));
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

	void Sound::Set(bool isLoop, UINT32 playBegin, UINT32 playLength, UINT32 loopBegin, UINT32 loopLength)
	{
		if (paused) return;
		std::pair<IXAudio2SourceVoice*, XAUDIO2_BUFFER> source = Storage.at(Content);		

		if (isLoop) source.second.LoopCount = XAUDIO2_LOOP_INFINITE;
		else source.second.LoopCount = 0;
		source.second.PlayBegin = playBegin;
		source.second.PlayLength = playLength;
		source.second.LoopBegin = loopBegin;
		source.second.LoopLength = loopLength;

		MUST(source.first->SubmitSourceBuffer(&source.second));
	}

	void Sound::Play()
	{
		std::pair<IXAudio2SourceVoice*, XAUDIO2_BUFFER> source = Storage.at(Content);
		paused = false;
		MUST(source.first->Start(0));
	}

	void Sound::Pause()
	{
		std::pair<IXAudio2SourceVoice*, XAUDIO2_BUFFER> source = Storage.at(Content);
		paused = true;
		MUST(source.first->Stop());
	}

	void Sound::Stop()
	{
		std::pair<IXAudio2SourceVoice*, XAUDIO2_BUFFER> source = Storage.at(Content);
		paused = false;
		MUST(source.first->Stop());
		MUST(source.first->FlushSourceBuffers());
	}

	void Sound::SetVolume(float const& volume)
	{
		std::pair<IXAudio2SourceVoice*, XAUDIO2_BUFFER> source = Storage.at(Content);
		source.first->SetVolume(volume);
	}
}