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
		ColourDisplay(gfx::Rectangle rect, const char* name, const std::shared_ptr<gfx::Colour> & displayColour, SDL_Renderer* renderer);
		virtual ~ColourDisplay() = default;
		ColourDisplay(ColourDisplay const& that) = default;
		ColourDisplay(ColourDisplay&& that) = default;
		ColourDisplay& operator=(ColourDisplay const& that) = default;
		ColourDisplay& operator=(ColourDisplay&& that) = default;

		void updateColour();
		void setOutlineColour(gfx::Colour outlineColour);
		
		void draw() override;

	private:
		std::shared_ptr<gfx::Colour> displayColour_;
		SDL_Renderer* renderer_;
	};

}