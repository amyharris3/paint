#pragma once
#include "PAINT_Tool.h"
#include "WIN_SDLRenderer.h"

namespace gfx
{
	struct Coords;
}

namespace paint
{
	class Brush;
	class DrawWindow;
	
	class DrawTool final :
		public Tool
	{
	public:
		DrawTool() = delete;
		DrawTool(gfx::Colour colour);
		virtual ~DrawTool() = default;
		DrawTool(const DrawTool& that) = default;
		DrawTool(DrawTool&& that) = default;
		DrawTool& operator=(const DrawTool& that) = default;
		DrawTool& operator=(DrawTool&& that) = default;

		void toolFunction(gfx::Coords& mouseCoords, gfx::Coords& prevMouseCoords, gfx::Coords& startCoords, gfx::Rectangle refRect, win::SDLRenderer* renderer) override;
		void toolFunctionEnd(gfx::Coords& mouseCoords, gfx::Coords& prevMouseCoords, gfx::Coords& startCoords, gfx::Rectangle refRect, win::SDLRenderer* renderer) override;
		void setToolColour(const uint8_t RGBA[]) override;

	private:
		uint8_t drawRGBA_[4];

	};


}
