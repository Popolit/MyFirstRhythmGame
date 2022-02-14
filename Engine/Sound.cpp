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
	class VoiceCallback final : public IXAudio2VoiceCallback
	{
	public:
		bool End, LoopEnd;
		VoiceCallback()
		{
			End = false;
			LoopEnd = false;
		}
		~VoiceCallback() { }
		void STDMETHODCALLTYPE OnStreamEnd() {}
		void STDMETHODCALLTYPE OnVoiceProcessingPassEnd() {}
		void STDMETHODCALLTYPE OnVoiceProcessingPassStart(UINT32 SamplesRequired) {}
		void STDMETHODCALLTYPE OnBufferEnd(void* pBufferContext) { End = true; }
		void STDMETHODCALLTYPE OnBufferStart(void* pBufferContext) { End = false; }
		void STDMETHODCALLTYPE OnLoopEnd(void* pBufferContext) { LoopEnd = true; }
		void STDMETHODCALLTYPE OnVoiceError(void* pBufferContext, HRESULT Error) {}
	};



	namespace
	{
		IXAudio2* XAudio2 = nullptr;	//XAudio 엔진 디바이스
		IXAudio2MasteringVoice* MasterVoice = nullptr;	//오디오 캡슐화 오디오 그래프를 통과하는 모든 오디오의 최종대상

		WAVEFORMATEXTENSIBLE wfx = { 0 };	//WAVE 형식을 저장함
		VoiceCallback callback;
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

	struct Handle final 
	{
		IXAudio2SourceVoice* SourceVoice = nullptr;
		XAUDIO2_BUFFER       buffer = { 0 };
	};

	std::map<std::string, Handle*> Storage;

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

		DWORD dwAudioSize = DWORD();
		DWORD dwAudioPosition = DWORD();
		MUST(FindAudio(hFile, fourccRIFF, dwAudioSize, dwAudioPosition));
		DWORD fileType = DWORD();
		MUST(ReadAudioData(hFile, &fileType, sizeof(DWORD), dwAudioPosition));
		if (fileType != fourccWAVE) return;

		MUST(FindAudio(hFile, fourccFMT, dwAudioSize, dwAudioPosition));
		MUST(ReadAudioData(hFile, &wfx, dwAudioSize, dwAudioPosition));

		MUST(FindAudio(hFile, fourccDATA, dwAudioSize, dwAudioPosition));
		BYTE* pDataBuffer = new BYTE[dwAudioSize];
		MUST(ReadAudioData(hFile, pDataBuffer, dwAudioSize, dwAudioPosition));

		Handle* handle = new Handle();
		handle->buffer.AudioBytes = dwAudioSize;
		handle->buffer.pAudioData = pDataBuffer;
		handle->buffer.Flags = XAUDIO2_END_OF_STREAM;

		MUST(XAudio2->CreateSourceVoice(&handle->SourceVoice, (WAVEFORMATEX*)&wfx, 0, XAUDIO2_DEFAULT_FREQ_RATIO, &callback));

		{
			size_t const x = file.find_first_of('/') + sizeof(char);
			size_t const y = file.find_last_of('.');

			Storage.try_emplace(file.substr(x, y - x), handle);
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
		Handle*& sound = Storage.at(Content);

		if (loop)
		{
			sound->buffer.LoopCount = XAUDIO2_LOOP_INFINITE;
			sound->buffer.PlayBegin = loopBegin * 44;
			sound->buffer.LoopBegin = loopBegin * 44;
			sound->buffer.LoopLength = loopLength;
		}
		else
		{
			sound->buffer.LoopCount = 0;
			sound->buffer.PlayBegin = 0;
			sound->buffer.LoopBegin = 0;
			sound->buffer.LoopLength = 0;
		}
		if (pause)
		{
			pause = false;
			MUST(sound->SourceVoice->Start());
			return;
		}

		MUST(sound->SourceVoice->Stop());
		MUST(sound->SourceVoice->FlushSourceBuffers());
		MUST(sound->SourceVoice->SubmitSourceBuffer(&sound->buffer));
		MUST(sound->SourceVoice->SetVolume(volume));
		MUST(sound->SourceVoice->Start());
	}

	void Sound::Pause()
	{
		if (pause) return;
		Handle*& sound = Storage.at(Content);
		pause = true;
		MUST(sound->SourceVoice->Stop());
	}

	void Sound::Stop()
	{
		Handle*& sound = Storage.at(Content);
		MUST(sound->SourceVoice->Stop());
		MUST(sound->SourceVoice->FlushSourceBuffers());	
		pause = false;
	}

	void Sound::SetVolume()
	{
		Handle*& sound = Storage.at(Content);
		sound->SourceVoice->SetVolume(volume);
	}

	bool Sound::isLoopEnd()
	{
		if (callback.LoopEnd)
		{
			callback.LoopEnd = false;
			return true;
		}
		return false;
	}
}