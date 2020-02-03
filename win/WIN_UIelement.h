#pragma once

#include "GFX_Colour.h"
#include "GFX_Rectangle.h"
#include <memory>
#include <string>

namespace win
{
	enum class MouseButton;
	class Container;

	class UIelement
	{
	private:
		std::string name_;
		gfx::Colour foregroundColour_;
		gfx::Colour backgroundColour_;
		gfx::Rectangle rect_;
		UIelement * parent_;

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
		void getForegroundColour(uint8_t rgba[]);
		void getBackgroundColour(uint8_t rgba[]);
		virtual void swapFgBgColours();

		void setRect(const gfx::Rectangle & rect);
		gfx::Rectangle getRect() const { return rect_; }
		const char* getName() const { return name_.c_str(); }
		UIelement* getParent() const { return parent_; }
		void setParent(UIelement * parent);

		virtual void draw() = 0;
		virtual void update() { };
		virtual void updateAndRerender() { };
		//virtual void mouseMove(int x, int y) {}
		virtual bool mouseEnter();
		virtual bool mouseExit();
		virtual bool mouseMove() { return false; };
		virtual bool mouseButtonDown(MouseButton button);
		virtual bool mouseButtonUp(MouseButton button) { return false; };
	};
}
