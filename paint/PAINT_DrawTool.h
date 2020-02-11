#pragma once
#include "PAINT_Tool.h"
#include <GFX_Renderer.h>

namespace win
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
		DrawTool(gfx::Renderer* renderer);
		virtual ~DrawTool() = default;
		DrawTool(const DrawTool& that) = default;
		DrawTool(DrawTool&& that) = default;
		DrawTool& operator=(const DrawTool& that) = default;
		DrawTool& operator=(DrawTool&& that) = default;

		void toolFunction(win::Coords& mouseCoords, win::Coords& prevMouseCoords, win::Coords& startCoords, gfx::Rectangle refRect) override;
		void toolFunctionEnd(win::Coords& mouseCoords, win::Coords& prevMouseCoords, win::Coords& startCoords, gfx::Rectangle refRect) override;
		void setToolColour(const uint8_t RGBA[]) override;
		void toolFunction(win::Coords relCoords, win::Coords prevRelCoords) override;
		void drawLines() const;

	private:
		gfx::Renderer* renderer_;
		uint8_t drawRGBA_[4];

	};


}
