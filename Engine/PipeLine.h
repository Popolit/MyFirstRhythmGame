#pragma once

namespace Rendering::Pipeline
{
	namespace Texture
	{
		void Create(struct Handle * &handle, SIZE const size, BYTE const * const data);
		void Render(struct Handle const* const &handle, RECT const area);
		void Delete(struct Handle const* const &handle);
	}

	namespace String
	{
		void Render(HFONT const hFont, LPCSTR const string, COLORREF const color, SIZE const size, POINT const center);
	}
	namespace Transform
	{
		//변환 전, 변환 후
		enum class Type
		{
			Former,
			Latter
		};

		using Matrix = float[4][4];

		template<Type type>
		void Update(Matrix const& matrix);
	}
}

