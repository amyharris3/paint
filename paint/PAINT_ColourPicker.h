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
		ColourPicker(gfx::Rectangle rect, SDL_Renderer* renderer, std::shared_ptr<DrawWindow> const & drawWindow);
		~ColourPicker() = default;
		ColourPicker(const ColourPicker & that) = default;
		ColourPicker(ColourPicker && that) = default;
		ColourPicker& operator=(const ColourPicker & that) = default;
		ColourPicker& operator=(ColourPicker && that) = default;

		void draw() override;
		void mouseButtonDown(win::MouseButton const b, int const xPixel, int const yPixel) override;
		
	private:

		std::shared_ptr<DrawWindow> drawWindowPtr_;
		SDL_Renderer* renderer_;
		Container displayBox_;
		std::shared_ptr<win::ColourDisplay> fgDisplay_;
		std::shared_ptr<win::ColourDisplay> bgDisplay_;
		
		
	};
}
