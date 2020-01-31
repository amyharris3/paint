#pragma once
#include "GFX_Rectangle.h"
#include "sdl.h"
#include "WIN_Slider.h"
#include "WIN_UIelement.h"

namespace win
{
	// Currently set to work horizontally along X axis
	class Slider : public UIelement
	{
	public:
		Slider() = default;
		Slider(SDL_Renderer* renderer, gfx::Rectangle rect, const char* name, gfx::Colour fillColour, gfx::Colour outlineColour, int const initialPos, int const slideMin, int const slideMax);
		virtual ~Slider() = default;
		Slider(Slider const& that) = default;
		Slider(Slider && that) = default;
		Slider& operator=(Slider const& that) = default;
		Slider& operator=(Slider && that) = default;

		void updateLineMarker();
		
		gfx::Rectangle getLineRect() const { return lineRect_; }
		gfx::Rectangle getMarkerRect() const { return markerRect_; }
		
		bool getHold() const { return holdMarker_; }
		void holdOn() { holdMarker_ = true; }
		void holdOff() { holdMarker_ = false; }

		void positionFromValue(int const val);
		int valueFromPosition();

		void moveMarker();
		void update();
		void updateAndRerender();
		void draw() override;

		bool mouseExit() override;
		bool mouseMove() override;
		bool mouseButtonDown(MouseButton button) override;
		bool mouseButtonUp(MouseButton button) override;
		
	private:

		SDL_Renderer* renderer_;
		
		int slideLineMin_;
		int slideLineMax_;
		gfx::Rectangle lineRect_;
		gfx::Colour lineColour_;

		int markerPos_;
		gfx::Rectangle markerRect_;
		gfx::Colour markerColour_;
		bool holdMarker_;

	};
	
}
