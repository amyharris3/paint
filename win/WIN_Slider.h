#pragma once
#include "GFX_Rectangle.h"
#include "WIN_Slider.h"
#include "WIN_UIelement.h"

namespace gfx {
	class Renderer;
}

namespace win
{
	// Currently set to work horizontally along X axis
	// Conversion between value <-> marker position is only approximate unless pixel<->value scaling is exact
	class Slider : public UIelement
	{
	public:
		Slider() = delete;
		Slider(gfx::Renderer* renderer, gfx::Rectangle rect, const char* name, gfx::Colour fillColour, gfx::Colour outlineColour, int initialVal, int slideMin, int slideMax);
		virtual ~Slider() = default;
		Slider(Slider const& that) = default;
		Slider(Slider && that) = default;
		Slider& operator=(Slider const& that) = default;
		Slider& operator=(Slider && that) = default;

		void updateLineMarker();

		gfx::Renderer* getRenderer() const { return renderer_; }
		gfx::Rectangle getLineRect() const { return lineRect_; }
		gfx::Rectangle getMarkerRect() const { return markerRect_; }
		int getMarkerValue() const { return markerVal_; }
		int getMarkerPos() const { return markerRect_.x; }
		
		bool getHold() const { return holdMarker_; }
		void holdOn() { holdMarker_ = true; }
		void holdOff() { holdMarker_ = false; }
		bool getClickDownFromOutside() const { return clickDownOutsideSlider_; }
		void setClickDownFromOutside(const bool b) { clickDownOutsideSlider_ = b; }
		
		int getApproxPositionFromValue() const;
		int getApproxValueFromPosition() const;

		void setMarkerValue(int val);
		void setMarkerPos(int x);
		
		void moveMarker(const int x);
		void update() override;
		void updateAndRerender() override;
		void draw() override;

		bool mouseEnter(bool clicked = false) override;
		bool mouseExit(bool clicked = false) override;
		bool mouseMove(SDL_MouseMotionEvent& e) override;
		bool mouseButtonDown(MouseButton button) override;
		bool mouseButtonUp(MouseButton button) override;
		
	private:

		gfx::Renderer* renderer_;
		
		int slideValueMin_;
		int slideValueMax_;
		gfx::Rectangle lineRect_;
		gfx::Colour lineColour_;

		// the position of the marker is stored in markerVal_ (for abstract value) and markerRect_.x (for physical pixel location)
		// markerVal_ should be used as the 'real' value, with markerRect_.x being a representation of it
		// also have 'true' values to keep internally, as otherwise causes rounding issues when converting between double and int
		int markerVal_;
		gfx::Rectangle markerRect_;
		gfx::Colour markerColour_;
		bool holdMarker_;

		bool clickDownOutsideSlider_;
	};
	
}
