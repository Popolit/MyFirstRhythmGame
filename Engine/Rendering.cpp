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
