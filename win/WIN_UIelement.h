#pragma once

#include "GFX_Colour.h"
#include "GFX_Rectangle.h"

namespace win
{
	enum class MouseButton;

	class UIelement
	{
	public:

		UIelement() = delete;
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
		void getForegroundColour(uint8_t rgba[]) const;
		void getBackgroundColour(uint8_t rgba[]) const;
		virtual void swapColours();

		void setRect(const gfx::Rectangle & rect);
		gfx::Rectangle getRect() const { return rect_; }
		const char* getName() const { return name_.c_str(); }
		UIelement* getParent() const { return parent_; }
		void setParent(UIelement * parent);

		virtual void draw() = 0;
		virtual void mouseEnter();
		virtual void mouseExit();
		virtual void mouseButtonDown(MouseButton) {};
		virtual void mouseButtonUp(MouseButton) {};
		virtual void earlyExit(MouseButton) {};

		typedef void (*ActionFunction)(UIelement* control);

	private:
		std::string name_;
		gfx::Colour foregroundColour_;
		gfx::Colour backgroundColour_;
		gfx::Rectangle rect_;
		UIelement* parent_;
	};
}
