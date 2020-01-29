#pragma once
#include "WIN_UIelement.h"
#include <SDL.h>
#include <memory>

struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Rect;

namespace win
{
	class ColourDisplay final : public UIelement
	{
	public:

		ColourDisplay() = delete;
		ColourDisplay(gfx::Rectangle rect, const char* name, const std::shared_ptr<gfx::Colour> & displayColour, SDL_Renderer* renderer, bool isActive);
		virtual ~ColourDisplay() = default;
		ColourDisplay(ColourDisplay const& that) = default;
		ColourDisplay(ColourDisplay&& that) = default;
		ColourDisplay& operator=(ColourDisplay const& that) = default;
		ColourDisplay& operator=(ColourDisplay&& that) = default;

		void updateColour(gfx::Colour colour);
		bool isActive() const { return isActive_; }
		void setActive();
		void setInactive();
		void swapActive();
		void setOutlineColour(const gfx::Colour outlineColour);
		
		void draw() override;
		void mouseExit() override;
		void mouseButtonDown(win::MouseButton const button) override;
		void mouseButtonUp(MouseButton button) override;

	private:
		SDL_Renderer* renderer_;
		bool isActive_;
		bool isClicked_;
	};

}