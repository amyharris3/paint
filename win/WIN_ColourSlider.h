#pragma once
#include "WIN_Slider.h"

namespace win
{
	class ColourSlider : public Slider
	{
	public:
		ColourSlider() = delete;
		ColourSlider(gfx::Renderer* renderer, gfx::Rectangle rect, const char* name, gfx::Colour fillColour, gfx::Colour outlineColour, uint8_t* linkedVariablePrimary, uint8_t* linkedVariableSecondary, bool primaryActive);
		virtual ~ColourSlider() = default;
		ColourSlider(ColourSlider const& that) = default;
		ColourSlider(ColourSlider && that) = default;
		ColourSlider& operator=(ColourSlider const& that) = default;
		ColourSlider& operator=(ColourSlider && that) = default;

		void valueChangedByMovement() const;
		void valueChangedExternally();

		void primaryActiveSwitch() { primaryActive_ = !primaryActive_; }
		
		bool mouseMove() override;
		bool mouseButtonUp(MouseButton button) override;
		
	private:

		uint8_t* linkedVariablePrimary_;
		uint8_t* linkedVariableSecondary_;
		bool primaryActive_; //else secondary is active
		
	};
}
