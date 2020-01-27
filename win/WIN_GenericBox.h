#pragma once

#include "WIN_UIelement.h"
#include <SDL.h>

struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Rect;

namespace win
{
	class GenericBox final : public UIelement
	{
	public:

		GenericBox() = delete;
		GenericBox(gfx::Rectangle& rect, const char* name, gfx::Colour foregroundColour, gfx::Colour backgroundColour, SDL_Renderer* renderer);
		virtual ~GenericBox() = default;
		GenericBox(GenericBox const& that) = default;
		GenericBox(GenericBox && that) = default;
		GenericBox& operator=(GenericBox const& that) = default;
		GenericBox& operator=(GenericBox && that) = default;

		void draw() override;

	private:
		SDL_Renderer* renderer_;
		//SDL_Rect boxRect_;
	};
	
}