#pragma once
#include "WIN_UIelement.h"

namespace gfx
{
	class Renderer;
}
namespace win
{
	class ColourDisplay final : public UIelement
	{
	public:

		ColourDisplay() = delete;
		ColourDisplay(gfx::Rectangle rect, const char* name, uint8_t displayColour[], gfx::Renderer* renderer, bool isActive);
		virtual ~ColourDisplay() = default;
		ColourDisplay(ColourDisplay const& that) = default;
		ColourDisplay(ColourDisplay&& that) = default;
		ColourDisplay& operator=(ColourDisplay const& that) = default;
		ColourDisplay& operator=(ColourDisplay&& that) = default;

		gfx::Colour getColour() const { return getForegroundColour(); }
		
		void setColour(gfx::Colour colour);
		bool isActive() const { return isActive_; }
		void setActive();
		void setInactive();
		void swapIsActive();
		void setOutlineColour(gfx::Colour outlineColour);
		void setClickFalse() { isClicked_ = false; }

		void update() override;
		void draw() override;
		bool mouseExit() override;
		bool mouseButtonDown(win::MouseButton button) override;
		bool mouseButtonUp(MouseButton button) override;

	private:
		gfx::Renderer* renderer_;
		bool isActive_;
		bool isClicked_;
		
	};

}