#pragma once
#include "GFX_Line.h"
#include "GFX_Coords.h"
#include "GFX_Rectangle.h"

namespace win {
	class SDLRenderer;
}

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
		virtual bool toolFunction(gfx::Coords& mouseCoords, gfx::Coords& prevMouseCoords, gfx::Coords& startCoords, gfx::Rectangle refRect, win::SDLRenderer* renderer) = 0;
		virtual bool toolFunctionEnd(gfx::Coords& mouseCoords, gfx::Coords& prevMouseCoords, gfx::Coords& startCoords, gfx::Rectangle refRect, win::SDLRenderer* renderer) = 0;
		void setALine(gfx::Line line);
		void setLines(std::vector<gfx::Line> lines);

		std::shared_ptr<Brush> getActiveBrush() const { return activeBrush_; }
		std::vector<gfx::Line> getLines() const { return lines_; }

		virtual void setToolColour(const uint8_t RGBA[]) = 0;
		virtual void setToolThickness(int thickness) = 0;
		
	private:
		
		std::vector<gfx::Line> lines_;
		std::shared_ptr<Brush> activeBrush_;
		uint8_t drawRGBA_[4];

	};
}