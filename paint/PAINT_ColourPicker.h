#pragma once
#include "WIN_Container.h"
#include "WIN_ColourDisplay.h"
#include "WIN_Button.h"

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

		void setDrawColour();
		void swapActiveColour();
		void updateFromDrawWindow();
		
		void draw() override;
		void mouseButtonDown(win::MouseButton const button) override;
		void mouseButtonUp(win::MouseButton const button) override;
		
	private:

		std::shared_ptr<DrawWindow> drawWindowPtr_;
		SDL_Renderer* renderer_;
		std::shared_ptr<Container> displayBox_;
		std::shared_ptr<win::ColourDisplay> primaryColourDisplay_;
		std::shared_ptr<win::ColourDisplay> secondaryColourDisplay_;
		std::shared_ptr<win::Button> swapButton_;
		
		bool clickDownOnColourDisplay_;
		
	};
}
