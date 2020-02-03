#pragma once
#include "WIN_Slider.h"

namespace win
{
	class ColourSlider : public Slider
	{
	public:
		ColourSlider() = delete;
		ColourSlider(SDL_Renderer * renderer, gfx::Rectangle rect, const char* name, gfx::Colour fillColour, gfx::Colour outlineColour, uint8_t* linkedVariable);
		virtual ~ColourSlider() = default;
		ColourSlider(ColourSlider const& that) = default;
		ColourSlider(ColourSlider && that) = default;
		ColourSlider& operator=(ColourSlider const& that) = default;
		ColourSlider& operator=(ColourSlider && that) = default;

		void valueChangedByMovement() const;
		void valueChangedExternally();

		bool mouseMove() override;
		bool mouseButtonUp(MouseButton button) override;
		
	private:

		uint8_t* linkedVariable_;
		
	};
}
