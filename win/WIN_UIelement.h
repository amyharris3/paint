#pragma once

#include "GFX_Colour.h"
#include "GFX_Rectangle.h"

namespace win
{
	enum class MouseButton;

	class UIelement
	{
	private:
		gfx::Colour foregroundColour_;
		gfx::Colour backgroundColour_;
		gfx::Rectangle rect_;


	public:
		const char* name_;

		UIelement() = default;
		UIelement(gfx::Rectangle rect, const char* name);
		virtual ~UIelement() = default;
		UIelement(UIelement const& that) = default;
		UIelement(UIelement && that) = default;
		UIelement& operator=(UIelement const& that) = default;
		UIelement & operator=(UIelement && that) = default;


		void setForegroundColour(gfx::Colour fgColour);
		void setBackgroundColour(gfx::Colour bgColour);
		gfx::Colour getBackgroundColour() const { return backgroundColour_; }
		gfx::Colour getForegroundColour() const { return foregroundColour_; }
		gfx::Rectangle getRect() const { return rect_; }
		const char* getName() { return name_; }

		virtual void draw() = 0;
		//virtual void mouseMove(int x, int y) {}
		virtual void mouseEnter();
		virtual void mouseExit();
		virtual void mouseButtonDown(MouseButton b, int xPixel, int yPixel);
		//virtual void mouseButtonUp(MouseButton button) {}
	};
}
