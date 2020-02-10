#pragma once
#include "GFX_Line.h"
#include "WIN_Coords.h"
#include "GFX_Rectangle.h"

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
		Tool(Tool && that) = default;
		Tool& operator=(const Tool & that) = default;
		Tool& operator=(Tool && that) = default;

		void setActiveBrush(std::shared_ptr<Brush> brush);
		void clearLines();
		virtual void toolFunction(win::Coords mouseCoords = { 0,0 }, win::Coords prevMouseCoords = { 0,0 }, win::Coords startCoords = { 0,0 }, gfx::Rectangle refRect = {0,0,0,0}) = 0;
		std::shared_ptr<Brush> getActiveBrush() const {return activeBrush_;}
		void renderLines(SDL_Renderer* renderer, const std::vector<gfx::Line>& lines) const;
		virtual void toolFunctionEnd(win::Coords mouseCoords, win::Coords prevMouseCoords, win::Coords startCoords, gfx::Rectangle refRect) = 0;

	protected:
		std::vector<gfx::Line> lines_;
		std::shared_ptr<Brush> activeBrush_;
		
	};
}
