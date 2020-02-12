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
		DrawTool(win::SDLRenderer* renderer);
		virtual ~DrawTool() = default;
		DrawTool(const DrawTool& that) = default;
		DrawTool(DrawTool&& that) = default;
		DrawTool& operator=(const DrawTool& that) = default;
		DrawTool& operator=(DrawTool&& that) = default;

		void toolFunction(win::Coords& mouseCoords, win::Coords& prevMouseCoords, win::Coords& startCoords, gfx::Rectangle refRect) override;
		void toolFunctionEnd(win::Coords& mouseCoords, win::Coords& prevMouseCoords, win::Coords& startCoords, gfx::Rectangle refRect) override;
		void setToolColour(const uint8_t RGBA[]) override;
		void toolFunction(gfx::Coords relCoords, gfx::Coords prevRelCoords) override;
		void drawLines() const;

	private:
		win::SDLRenderer* renderer_;
		uint8_t drawRGBA_[4];

	};


}
