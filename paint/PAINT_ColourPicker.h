#pragma once
#include "WIN_Container.h"
#include "WIN_ColourDisplay.h"

namespace paint
{
	class DrawWindow;

	class ColourPicker final : public win::Container
	{
	public:
		
		ColourPicker() = delete;
		ColourPicker(gfx::Rectangle rect, SDL_Renderer* renderer, DrawWindow* drawWindow);
		~ColourPicker() = default;
		ColourPicker(const ColourPicker & that) = default;
		ColourPicker(ColourPicker && that) = default;
		ColourPicker& operator=(const ColourPicker & that) = default;
		ColourPicker& operator=(ColourPicker && that) = default;

	private:
		
		Container displayBox_;
		win::ColourDisplay fgDisplay_;
		win::ColourDisplay bgDisplay_;
		
	};
}
