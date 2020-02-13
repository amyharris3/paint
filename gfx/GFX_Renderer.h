#pragma once
#include <vector>
#include "GFX_Text.h"

namespace gfx
{
	class Colour;
	class Rectangle;
	class Line;

	enum class RenderTarget
	{
		SCREEN,
		DRAW_WINDOW,
		TEMP_TEXTURE
	};
	
	// The purpose of the separate renderer class is to handle the SDL rendering, so as to allow the PAINT and WIN classes to function without needing to load SDL.
	// Will be dependent on all other classes as it needs to have the functionality to render each of them.
	// Default/empty constructor sets nullptr for the SDL renderer, use if necessary for unit testing, but do NOT use when actually rendering anything or it will cause assertion error.
	class Renderer
	{
	public:

		virtual void createDrawWindowTexture(Rectangle rect) = 0;
		virtual  void destroyDrawWindowTexture() = 0;

		virtual void renderPresentScreen() = 0;

		virtual void switchRenderTarget(RenderTarget target) = 0;

		virtual void renderBox(RenderTarget target, Rectangle rect, Colour) = 0;
		virtual void renderText(RenderTarget target, Text* text, int xPixel, int yPixel) = 0;
		virtual void renderTextbox(RenderTarget target, Rectangle rect, Colour colour, Text* text, int xOffset, int yOffset) = 0;
		virtual void renderLines(RenderTarget target, const std::vector<gfx::Line>& lines, int thickness, const uint8_t drawRGBA_[]) = 0;

		virtual void renderDrawWindowTexture(Rectangle rect, Colour colour, bool updateTexture_) const = 0;
		virtual void clearDrawWindow(Rectangle rect, gfx::Colour colour) = 0;

	protected:
		Renderer() = default;
		~Renderer() = default;
		Renderer(const Renderer& that) = default;
		Renderer(Renderer&& that) = default;
		Renderer& operator=(const Renderer& that) = default;
		Renderer& operator=(Renderer&& that) = default;

	};
}
