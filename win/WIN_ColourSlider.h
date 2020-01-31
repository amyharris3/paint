#pragma once
#include "WIN_Slider.h"

namespace win
{
	class ColourSlider : public Slider
	{
	public:
		ColourSlider() = default;
		ColourSlider(SDL_Renderer * renderer, gfx::Rectangle rect, const char* name, gfx::Colour fillColour, gfx::Colour outlineColour, uint8_t* linkedVariable);
		virtual ~ColourSlider() = default;
		ColourSlider(ColourSlider const& that) = default;
		ColourSlider(ColourSlider && that) = default;
		ColourSlider& operator=(ColourSlider const& that) = default;
		ColourSlider& operator=(ColourSlider && that) = default;

		void valueChangedByMovement();
		void valueChangedExternally();

		void mouseMove() override;
		void mouseButtonUp(MouseButton button) override;
		
	private:

		uint8_t* linkedVariable_;
		
	};
}
