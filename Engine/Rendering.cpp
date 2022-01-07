#define _USE_MATH_DEFINES
#include <Windows.h>
#include "Rendering.h"
#include "FreeImage.h"
#include "PipeLine.h"
#include "Time.h"
#include "Resource.h"

#include <map>
#include <string>
#include <cmath>


namespace Rendering
{
	namespace Pipeline
	{
		void Procedure(HWND const, UINT const, WPARAM const, LPARAM const);
	}

	namespace
	{
		inline Matrix<4, 4> Scale(Vector<2> const& length)
		{
			return Matrix<4, 4>
			{
				length[0], 0, 0, 0,
				0, length[1], 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1
			};
		}

		inline Matrix<4, 4> Rotation(float const& angle)
		{
			float const rad = static_cast<float>(M_PI) * angle / 180;
			return Matrix<4, 4>
			{
				cos(rad), -sin(rad), 0, 0,
				sin(rad), cos(rad), 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1
			};
		}

		inline Matrix<4, 4> Translation(Vector<2> const& location)
		{
			return Matrix<4, 4>
			{
				1, 0, 0, location[0],
				0, 1, 0, location[1],
				0, 0, 1, 0,
				0, 0, 0, 1
			};
		}
	}

	void Camera::Set() const
	{
		using namespace Pipeline;

		Matrix<4, 4> const projection = Scale(Vector<2>(2 / Length[0], 2 / Length[1]));
		Matrix<4, 4> const view = Rotation(-Angle) * Translation(-Location);
		Matrix<4, 4> const latter = projection * view;

		Transform::Update<Transform::Type::Latter>(reinterpret_cast<Transform::Matrix const&>(latter));
	}

	namespace Text
	{
		void Import(std::string const& file)
		{
			AddFontResourceEx(file.data(), FR_PRIVATE | FR_NOT_ENUM, nullptr);
		}
		void Component::Draw()
		{
			LOGFONT descriptor = LOGFONT();

			descriptor.lfHeight = Font.Size;
			descriptor.lfWeight = Font.Bold ? FW_BOLD : FW_NORMAL;
			descriptor.lfItalic = Font.Italic;
			descriptor.lfUnderline = Font.Underlined;
			descriptor.lfStrikeOut = Font.StrikeThrough;
			descriptor.lfCharSet = DEFAULT_CHARSET;//운영체재나 한국어, 중국어 등에 따라 적용 안될 경우


			strcpy_s(descriptor.lfFaceName, LF_FACESIZE, Font.Name);
			HFONT const font = CreateFontIndirect(&descriptor);

			SIZE const area = { static_cast<LONG>(Length[0]), static_cast<LONG>(Length[1]) };
			POINT const center = { static_cast<LONG>(Location[0]), static_cast<LONG>(Location[1]) };

			Pipeline::String::Render(font, Content, RGB(Color.Red, Color.Green, Color.Blue), area, center);

			DeleteObject(font);
		}
	}

	namespace Image
	{
		struct Descriptor final
		{
		public:
			Pipeline::Texture::Handle* Handle = nullptr;
		public:
			SIZE Size = SIZE();	
		};

		std::map<std::string, Descriptor> Storage;

		void Import(std::string const& file)
		{
			FIBITMAP* bitmap = FreeImage_Load(FreeImage_GetFileType(file.data()), file.data());
			FreeImage_FlipVertical(bitmap);

			//32비트가 아니면 오류가 날수도 있으니, 32비트로 수정
			if (FreeImage_GetBPP(bitmap) != 32)
			{
				FIBITMAP* const previous = bitmap;

				bitmap = FreeImage_ConvertTo32Bits(bitmap);

				FreeImage_Unload(previous);
			}
			Image::Descriptor descriptor = Image::Descriptor();
			{
				descriptor.Size.cx = FreeImage_GetWidth(bitmap);
				descriptor.Size.cy = FreeImage_GetHeight(bitmap);
				Pipeline::Texture::Create(descriptor.Handle, descriptor.Size, FreeImage_GetBits(bitmap));
			}
			{
				size_t const x = file.find_first_of('/') + sizeof(char);
				size_t const y = file.find_last_of('.');

				Image::Storage.try_emplace(file.substr(x, y - x), descriptor);
			}
			FreeImage_Unload(bitmap);
		}
		void Component::Draw()
		{
			using namespace Pipeline;
			{
				Matrix<4, 4> const world = Translation(Location) * Rotation(Angle) * Scale(Length);
				Transform::Update<Transform::Type::Former>(reinterpret_cast<Transform::Matrix const&>(world));
			}
			{
				Descriptor const&image = Storage.at(Content);

				Texture::Render(image.Handle, { 0, 0, image.Size.cx, image.Size.cy });
			}
		}
	}
	
	namespace Animation
	{
		struct Descriptor final
		{
		public:
			Pipeline::Texture::Handle* Handle = nullptr;
		public:
			UINT Motion = UINT();
			SIZE Frame = SIZE();
		};

		std::map<std::string, Descriptor> Storage;

		void Import(std::string const& file)
		{
			FIBITMAP* bitmap = FreeImage_Load(FreeImage_GetFileType(file.data()), file.data());
			FreeImage_FlipVertical(bitmap);

			//32비트가 아니면 오류가 날수도 있으니, 32비트로 수정
			if (FreeImage_GetBPP(bitmap) != 32)
			{
				FIBITMAP* const previous = bitmap;

				bitmap = FreeImage_ConvertTo32Bits(bitmap);

				FreeImage_Unload(previous);
			}
			Animation::Descriptor descriptor = Animation::Descriptor();
			{
				descriptor.Frame.cx = FreeImage_GetWidth(bitmap);
				descriptor.Frame.cy = FreeImage_GetHeight(bitmap);
				Pipeline::Texture::Create(descriptor.Handle, descriptor.Frame, FreeImage_GetBits(bitmap));
			}
			{
				size_t const x = file.find_first_of('/') + sizeof(char);
				size_t const y = file.find_last_of('[') + sizeof(char);
				size_t const z = file.find_last_of(']');
				descriptor.Motion = atoi(file.substr(y, z - y).data());
				descriptor.Frame.cx /= descriptor.Motion;
				Animation::Storage.try_emplace(file.substr(x, y - x - sizeof(char)), descriptor);
			}
			FreeImage_Unload(bitmap);
		}
		void Component::Draw()
		{
			using namespace Pipeline;
			{
				Matrix<4, 4> const world = Translation(Location) * Rotation(Angle) * Scale(Length);
				Transform::Update<Transform::Type::Former>(reinterpret_cast<Transform::Matrix const&>(world));
			}

			{
				Descriptor const& descriptor = Storage.at(Content);

				LONG const progress = static_cast<LONG>((Playback / Duration) * descriptor.Motion);
				RECT const area
				{
					descriptor.Frame.cx * (progress + Flipped.x),  descriptor.Frame.cy * Flipped.y,
					descriptor.Frame.cx * (progress + !Flipped.x), descriptor.Frame.cy * !Flipped.y
				};

				Texture::Render(descriptor.Handle, area);
				
				//시간 업데이트
				float const delta = Time::Get::Delta();
				Playback += delta;

				//fmod(x, y) : x / y의 부동 소수점 부분만 반환
				if (Duration * descriptor.Motion)
				{
					if (Repeatable) Playback = fmod(Playback, Duration);
					else Playback -= delta;
				}
			}
		}
	}

	namespace Sound
	{
		void Import(std::string const& file)
		{
			IDirectSoundBuffer* buffer;
			LoadWaveFile(file.data(), &buffer);

			HWND hWindow = HWND();
			Pipeline::Sound::Create(, &buffer);
		}
		void Component::Play()
		{

		}

		
		bool Sound::Initialize(HWND hwnd, std::string const& file)
		{
			// Initialize direct sound and the primary sound buffer.
			if (!InitializeDirectSound(hwnd))
			{
				return false;
			}

			// Load a wave audio file onto a secondary buffer.
			if (!LoadWaveFile("../Dx11Demo_14/data/sound01.wav", &m_secondaryBuffer1))
			{
				return false;
			}

			return PlayWaveFile();
		}


		void Sound::Shutdown()
		{
			// Release the secondary buffer.
			ShutdownWaveFile(&m_secondaryBuffer1);

			// Shutdown the Direct Sound API.
			ShutdownDirectSound();
		}


		bool Sound::InitializeDirectSound(HWND hwnd)
		{
			// Initialize the direct sound interface pointer for the default sound device.
			if (FAILED(DirectSoundCreate(NULL, &m_DirectSound, NULL)))
			{
				return false;
			}

			// Set the cooperative level to priority so the format of the primary sound buffer can be modified.
			if (FAILED(m_DirectSound->SetCooperativeLevel(hwnd, DSSCL_PRIORITY)))
			{
				return false;
			}

			// Setup the primary buffer description.
			DSBUFFERDESC bufferDesc;
			bufferDesc.dwSize = sizeof(DSBUFFERDESC);
			bufferDesc.dwFlags = DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRLVOLUME;
			bufferDesc.dwBufferBytes = 0;
			bufferDesc.dwReserved = 0;
			bufferDesc.lpwfxFormat = NULL;
			bufferDesc.guid3DAlgorithm = GUID_NULL;

			// Get control of the primary sound buffer on the default sound device.
			if (FAILED(m_DirectSound->CreateSoundBuffer(&bufferDesc, &m_primaryBuffer, NULL)))
			{
				return false;
			}

			// Setup the format of the primary sound bufffer.
			// In this case it is a .WAV file recorded at 44,100 samples per second in 16-bit stereo (cd audio format).
			WAVEFORMATEX waveFormat;
			waveFormat.wFormatTag = WAVE_FORMAT_PCM;
			waveFormat.nSamplesPerSec = 44100;
			waveFormat.wBitsPerSample = 16;
			waveFormat.nChannels = 2;
			waveFormat.nBlockAlign = (waveFormat.wBitsPerSample / 8) * waveFormat.nChannels;
			waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
			waveFormat.cbSize = 0;

			// Set the primary buffer to be the wave format specified.
			if (FAILED(m_primaryBuffer->SetFormat(&waveFormat)))
			{
				return false;
			}

			return true;
		}


		void Sound::ShutdownDirectSound()
		{
			// Release the primary sound buffer pointer.
			if (m_primaryBuffer)
			{
				m_primaryBuffer->Release();
				m_primaryBuffer = 0;
			}

			// Release the direct sound interface pointer.
			if (m_DirectSound)
			{
				m_DirectSound->Release();
				m_DirectSound = 0;
			}
		}


		bool Sound::LoadWaveFile(const char* filename, IDirectSoundBuffer** secondaryBuffer)
		{
			// Open the wave file in binary.
			FILE* filePtr = nullptr;
			int error = fopen_s(&filePtr, filename, "rb");
			if (error != 0)
			{
				return false;
			}

			// Read in the wave file header.
			WaveHeaderType waveFileHeader;
			UINT count = static_cast<UINT>(fread(&waveFileHeader, sizeof(waveFileHeader), 1, filePtr));
			if (count != 1)
			{
				return false;
			}

			// Check that the chunk ID is the RIFF format.
			if ((waveFileHeader.chunkId[0] != 'R') || (waveFileHeader.chunkId[1] != 'I') ||
				(waveFileHeader.chunkId[2] != 'F') || (waveFileHeader.chunkId[3] != 'F'))
			{
				return false;
			}

			// Check that the file format is the WAVE format.
			if ((waveFileHeader.format[0] != 'W') || (waveFileHeader.format[1] != 'A') ||
				(waveFileHeader.format[2] != 'V') || (waveFileHeader.format[3] != 'E'))
			{
				return false;
			}

			// Check that the sub chunk ID is the fmt format.
			if ((waveFileHeader.subChunkId[0] != 'f') || (waveFileHeader.subChunkId[1] != 'm') ||
				(waveFileHeader.subChunkId[2] != 't') || (waveFileHeader.subChunkId[3] != ' '))
			{
				return false;
			}

			// Check that the audio format is WAVE_FORMAT_PCM.
			if (waveFileHeader.audioFormat != WAVE_FORMAT_PCM)
			{
				return false;
			}

			// Check that the wave file was recorded in stereo format.
			if (waveFileHeader.numChannels != 2)
			{
				return false;
			}

			// Check that the wave file was recorded at a sample rate of 44.1 KHz.
			if (waveFileHeader.sampleRate != 44100)
			{
				return false;
			}

			// Ensure that the wave file was recorded in 16 bit format.
			if (waveFileHeader.bitsPerSample != 16)
			{
				return false;
			}

			// Check for the data chunk header.
			if ((waveFileHeader.dataChunkId[0] != 'd') || (waveFileHeader.dataChunkId[1] != 'a') ||
				(waveFileHeader.dataChunkId[2] != 't') || (waveFileHeader.dataChunkId[3] != 'a'))
			{
				return false;
			}

			// Set the wave format of secondary buffer that this wave file will be loaded onto.
			WAVEFORMATEX waveFormat;
			waveFormat.wFormatTag = WAVE_FORMAT_PCM;
			waveFormat.nSamplesPerSec = 44100;
			waveFormat.wBitsPerSample = 16;
			waveFormat.nChannels = 2;
			waveFormat.nBlockAlign = (waveFormat.wBitsPerSample / 8) * waveFormat.nChannels;
			waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
			waveFormat.cbSize = 0;

			// Set the buffer description of the secondary sound buffer that the wave file will be loaded onto.
			DSBUFFERDESC bufferDesc;
			bufferDesc.dwSize = sizeof(DSBUFFERDESC);
			bufferDesc.dwFlags = DSBCAPS_CTRLVOLUME;
			bufferDesc.dwBufferBytes = waveFileHeader.dataSize;
			bufferDesc.dwReserved = 0;
			bufferDesc.lpwfxFormat = &waveFormat;
			bufferDesc.guid3DAlgorithm = GUID_NULL;

			// Create a temporary sound buffer with the specific buffer settings.
			IDirectSoundBuffer* tempBuffer = nullptr;
			if (FAILED(m_DirectSound->CreateSoundBuffer(&bufferDesc, &tempBuffer, NULL)))
			{
				return false;
			}

			// Test the buffer format against the direct sound 8 interface and create the secondary buffer.
			if (FAILED(tempBuffer->QueryInterface(IID_IDirectSoundBuffer8, (void**)&*secondaryBuffer)))
			{
				return false;
			}

			// Release the temporary buffer.
			tempBuffer->Release();
			tempBuffer = 0;

			// Move to the beginning of the wave data which starts at the end of the data chunk header.
			fseek(filePtr, sizeof(WaveHeaderType), SEEK_SET);

			// Create a temporary buffer to hold the wave file data.
			unsigned char* waveData = new unsigned char[waveFileHeader.dataSize];
			if (!waveData)
			{
				return false;
			}

			// Read in the wave file data into the newly created buffer.
			count = static_cast<UINT>(fread(waveData, 1, waveFileHeader.dataSize, filePtr));
			if (count != waveFileHeader.dataSize)
			{
				return false;
			}

			// Close the file once done reading.
			error = fclose(filePtr);
			if (error != 0)
			{
				return false;
			}

			// Lock the secondary buffer to write wave data into it.
			unsigned char* bufferPtr = nullptr;
			unsigned long bufferSize = 0;
			if (FAILED((*secondaryBuffer)->Lock(0, waveFileHeader.dataSize, (void**)&bufferPtr, (DWORD*)&bufferSize, NULL, 0, 0)))
			{
				return false;
			}

			// Copy the wave data into the buffer.
			memcpy(bufferPtr, waveData, waveFileHeader.dataSize);

			// Unlock the secondary buffer after the data has been written to it.
			if (FAILED((*secondaryBuffer)->Unlock((void*)bufferPtr, bufferSize, NULL, 0)))
			{
				return false;
			}

			// Release the wave data since it was copied into the secondary buffer.
			delete[] waveData;
			waveData = 0;

			return true;
		}


		void Sound::ShutdownWaveFile(IDirectSoundBuffer** secondaryBuffer)
		{
			// Release the secondary sound buffer.
			if (*secondaryBuffer)
			{
				(*secondaryBuffer)->Release();
				*secondaryBuffer = 0;
			}
		}


		bool Sound::PlayWaveFile()
		{
			// Set position at the beginning of the sound buffer.
			if (FAILED(m_secondaryBuffer1->SetCurrentPosition(0)))
			{
				return false;
			}

			// Set volume of the buffer to 100%.
			if (FAILED(m_secondaryBuffer1->SetVolume(DSBVOLUME_MAX)))
			{
				return false;
			}

			// Play the contents of the secondary sound buffer.
			if (FAILED(m_secondaryBuffer1->Play(0, 0, 0)))
			{
				return false;
			}

			return true;
		}
	}


	void Procedure(HWND const hWindow, UINT const uMessage, WPARAM const wParameter, LPARAM const lParameter)
	{
		
		switch (uMessage)
		{
			case WM_CREATE:
			{
				Pipeline::Procedure(hWindow, uMessage, wParameter, lParameter);	
				
				Resource::Import("Font", Text::Import);

				FreeImage_Initialise();
				{
					Resource::Import("Image", Image::Import);
					Resource::Import("Animation", Animation::Import);
				}
				FreeImage_DeInitialise();

				return;
			}
			case WM_APP:
			{
				Pipeline::Procedure(hWindow, uMessage, wParameter, lParameter);

				return;
			}
			case WM_SIZE:
			{
				Pipeline::Procedure(hWindow, uMessage, wParameter, lParameter);

				return;
			}
			case WM_DESTROY:
			{
				for (std::pair<std::string, Image::Descriptor> const& pair : Image::Storage)
					Pipeline::Texture::Delete(pair.second.Handle);

				Pipeline::Procedure(hWindow, uMessage, wParameter, lParameter);

				return;
			}


		}
	}
}
