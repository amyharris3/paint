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

		void toolFunction(win::Coords& relCoords, win::Coords& prevRelCoords, win::Coords& startCoords, gfx::Rectangle refRect) override;
		void toolFunctionEnd(win::Coords& mouseCoords, win::Coords& prevMouseCoords, win::Coords& startCoords, gfx::Rectangle refRect) override;
		void setToolColour(const uint8_t RGBA[]) override {}
	};
}
