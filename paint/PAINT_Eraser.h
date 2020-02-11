#pragma once
#include "PAINT_Tool.h"

namespace paint
{
	class Eraser :
		public Tool
	{
	public:
		Eraser() = default;
		~Eraser() = default;
		Eraser(const Eraser& that) = default;
		Eraser(Eraser && that) = default;
		Eraser& operator=(const Eraser & that) = default;
		Eraser& operator=(Eraser && that) = default;

		void toolFunction(win::Coords relCoords, win::Coords prevRelCoords) override;
	};
}
