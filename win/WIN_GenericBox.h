#pragma once

#include "WIN_UIelement.h"
#include "GFX_Renderer.h"

struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Rect;

namespace win
{
	class GenericBox final : public UIelement
	{
	public:

		GenericBox() = delete;
		GenericBox(gfx::Rectangle& rect, const char* name, gfx::Colour foregroundColour, gfx::Colour backgroundColour);
		virtual ~GenericBox() = default;
		GenericBox(GenericBox const& that) = default;
		GenericBox(GenericBox && that) = default;
		GenericBox& operator=(GenericBox const& that) = default;
		GenericBox& operator=(GenericBox && that) = default;

		void draw(win::SDLRenderer* renderer) override;

	};
	
}