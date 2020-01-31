#pragma once
#include <iostream>
#include <vector>

namespace win
{
	struct Coords;
}

namespace paint
{
	class Brush;
	struct Line
	{
		int x1;
		int y1;
		int x2;
		int y2;

	};
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
		virtual void toolFunction(win::Coords mouseCoords, win::Coords prevMouseCoords) = 0;
		std::shared_ptr<Brush> getActiveBrush() const {return activeBrush_;}
		
	protected:
		std::vector<Line> lines_;
		std::shared_ptr<Brush> activeBrush_;
		
	};
}
