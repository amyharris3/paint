#pragma once
#include "WIN_Slider.h"

namespace win
{
	class ColourSlider : public Slider
	{
	public:
		ColourSlider() = delete;
		ColourSlider(gfx::Rectangle rect, const char* name, gfx::Colour fillColour, gfx::Colour outlineColour, uint8_t* linkedVariablePrimary, uint8_t* linkedVariableSecondary, bool primaryActive);
		virtual ~ColourSlider() = default;
		ColourSlider(ColourSlider const& that) = default;
		ColourSlider(ColourSlider && that) = default;
		ColourSlider& operator=(ColourSlider const& that) = default;
		ColourSlider& operator=(ColourSlider && that) = default;

		void valueChangedByMovement() const;
		void valueChangedExternally();

		void primaryActiveSwitch() { primaryActive_ = !primaryActive_; }
		
		bool mouseMove(SDL_MouseMotionEvent& e) override;
		bool mouseButtonUp(MouseButton button, win::SDLRenderer* renderer) override;
		
	private:

		uint8_t* linkedVariablePrimary_;
		uint8_t* linkedVariableSecondary_;
		bool primaryActive_; //else secondary is active
		
	};
}
