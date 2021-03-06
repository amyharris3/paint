#pragma once
#include "WIN_UIelement.h"

//struct SDL_Texture;
//struct SDL_Renderer;
//struct SDL_Rect;

namespace win {
	class SDLRenderer;
}

namespace paint
{
	class ColourDisplay final : public win::UIelement
	{
	public:

		ColourDisplay() = delete;
		ColourDisplay(gfx::Rectangle rect, const char* name, uint8_t displayColour[], bool isActive);
		virtual ~ColourDisplay() = default;
		ColourDisplay(ColourDisplay const& that) = default;
		ColourDisplay(ColourDisplay&& that) = default;
		ColourDisplay& operator=(ColourDisplay const& that) = default;
		ColourDisplay& operator=(ColourDisplay&& that) = default;

		//gfx::Colour getColour() const { return { *rPtr_, *gPtr_, *bPtr_, *aPtr_ }; }
		gfx::Colour getColour() const { return getForegroundColour(); }
		
		void setColour(gfx::Colour colour);
		//void setRGBA(uint8_t displayColour[]);
		//void updateColourFromRGBA();
		bool isActive() const { return isActive_; }
		void setActive();
		void setInactive();
		void swapIsActive();
		void setOutlineColour(gfx::Colour outlineColour);
		void setClickFalse() { isClicked_ = false; }

		void update() override;
		void draw(win::SDLRenderer* renderer) override;
		bool mouseEnter(win::MouseButton button, bool clicked = false) override;
		bool mouseExit(win::MouseButton button, bool clicked = false) override;
		bool mouseMove(SDL_MouseMotionEvent& e) override;
		bool mouseButtonDown(win::MouseButton button, bool clicked = false) override;
		bool mouseButtonUp(win::MouseButton button, bool clicked = false, win::SDLRenderer* renderer = nullptr) override;

	private:
		bool isActive_;
		bool isClicked_;
		bool mouseDragged_;

		/*uint8_t* rPtr_;
		uint8_t* gPtr_;
		uint8_t* bPtr_;
		uint8_t* aPtr_;*/
		
	};

}
