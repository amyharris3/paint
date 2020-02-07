#pragma once
#include "GFX_Line.h"
#include "WIN_Coords.h"

namespace paint
{
	class Brush;
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
		virtual void toolFunction(win::Coords relCoords, win::Coords prevRelCoords) = 0;
		std::shared_ptr<Brush> getActiveBrush() const {return activeBrush_;}

		virtual void setToolColour(const uint8_t RGBA[]) = 0;
		
	protected:
		std::vector<gfx::Line> lines_;
		std::shared_ptr<Brush> activeBrush_;
		
	};
}
