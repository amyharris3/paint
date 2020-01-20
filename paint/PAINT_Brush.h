#pragma once
#include "PAINT_Tool.h"
#include <vector>
#include "PAINT_DrawWindow.h"

//struct Coords
//{
//	int x;
//	int y;
//};
namespace paint
{
	struct Coords;

	class Brush :
		public Tool
	{
	public:
		Brush() = default;
		Brush(int thickness);
		virtual ~Brush() = default;
		Brush(const Brush& that) = default;
		Brush(Brush&& that) = default;
		Brush& operator=(const Brush& that) = default;
		Brush& operator=(Brush&& that) = default;

		std::vector<Coords> brushArea(Coords pixel);


	private:
		int thickness_;
	};
}
