#pragma once
#include "SDL.h"
#include "GFX_Renderer.h"

namespace win {

	// The purpose of the separate SDLRenderer class is to handle the SDL rendering, so as to allow the PAINT and WIN classes to function without needing to load SDL.
		// Will be dependent on all other classes as it needs to have the functionality to render each of them.
		// Default/empty constructor sets nullptr for the SDL SDLRenderer, use if necessary for unit testing, but do NOT use when actually rendering anything or it will cause assertion error.
	class SDLRenderer : public gfx::Renderer
	{
	public:
		SDLRenderer(); //should only be used in debug
		SDLRenderer(SDL_Renderer* SDLRenderer);
		virtual ~SDLRenderer();
		SDLRenderer(const SDLRenderer& that) = default;
		SDLRenderer(SDLRenderer&& that) = default;
		SDLRenderer& operator=(const SDLRenderer& that) = default;
		SDLRenderer& operator=(SDLRenderer&& that) = default;

		bool notDummy() const;

		SDL_Renderer* getSDLRenderer() const { return rendererSDL_; }

		void createDrawWindowTexture(gfx::Rectangle rect) override;
		void destroyDrawWindowTexture() override;

		void renderPresentScreen() override;

		void switchRenderTarget(gfx::RenderTarget target) override;

		void renderBox(gfx::RenderTarget target, gfx::Rectangle rect, gfx::Colour) override;
		void renderText(gfx::RenderTarget target, gfx::Text* text, int xPixel, int yPixel) override;
		void renderTextbox(gfx::RenderTarget target, gfx::Rectangle rect, gfx::Colour colour, gfx::Text* text, int xOffset, int yOffset) override;
		void renderLines(gfx::RenderTarget target, const std::vector<gfx::Line>& lines, int thickness, const uint8_t drawRGBA_[]) override;

		void renderDrawWindowTexture(gfx::Rectangle rect, gfx::Colour colour, bool updateTexture_) const override;
		void clearDrawWindow(gfx::Rectangle rect, gfx::Colour colour) override;

	private:
		SDL_Renderer* rendererSDL_;
		SDL_Texture* textureDW_;

		gfx::RenderTarget currentTarget_;



	};
}