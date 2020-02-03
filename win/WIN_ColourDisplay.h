#pragma once
#include "WIN_UIelement.h"
#include <SDL.h>

struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Rect;

namespace win
{
	class ColourDisplay final : public UIelement
	{
	public:

		ColourDisplay() = delete;
		ColourDisplay(gfx::Rectangle rect, const char* name, uint8_t displayColour[], SDL_Renderer* renderer, bool isActive);
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
		void draw() override;
		bool mouseExit() override;
		bool mouseButtonDown(win::MouseButton button) override;
		bool mouseButtonUp(MouseButton button) override;

	private:
		SDL_Renderer* renderer_;
		bool isActive_;
		bool isClicked_;

		/*uint8_t* rPtr_;
		uint8_t* gPtr_;
		uint8_t* bPtr_;
		uint8_t* aPtr_;*/
		
	};

}