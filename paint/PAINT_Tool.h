#pragma once
#include "GFX_Line.h"
#include "WIN_Coords.h"
#include "GFX_Rectangle.h"
//#include "PAINT_Brush.h"

namespace gfx
{
	class Renderer;
}

namespace paint
{
	class Brush;
	class Shape;
	class Tool
	{
	public:
		Tool();
		virtual ~Tool() = default;
		Tool(const Tool& that) = default;
		Tool(Tool&& that) = default;
		Tool& operator=(const Tool& that) = default;
		Tool& operator=(Tool&& that) = default;

		void setActiveBrush(std::shared_ptr<Brush> brush);
		void clearLines();
		virtual void toolFunction(win::Coords& mouseCoords, win::Coords& prevMouseCoords, win::Coords& startCoords, gfx::Rectangle refRect) = 0;
		std::shared_ptr<Brush> getActiveBrush() const { return activeBrush_; }
		//void renderLines(gfx::Renderer* renderer, const std::vector<gfx::Line>& lines) const;
		virtual void toolFunctionEnd(win::Coords& mouseCoords, win::Coords& prevMouseCoords, win::Coords& startCoords, gfx::Rectangle refRect) = 0;
		void setALine(gfx::Line line);
		void setLines(std::vector<gfx::Line> lines);
		std::vector<gfx::Line> getLines() const { return lines_; }

		virtual void setToolColour(const uint8_t RGBA[]) = 0;
	private:
		
		std::vector<gfx::Line> lines_;
		std::shared_ptr<Brush> activeBrush_;
		uint8_t drawRGBA_[4];

	};
}