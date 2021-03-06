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

		bool toolFunction(gfx::Coords& relCoords, gfx::Coords& prevRelCoords, gfx::Coords& startCoords, gfx::Rectangle refRect, win::SDLRenderer* renderer) override;
		bool toolFunctionEnd(gfx::Coords& mouseCoords, gfx::Coords& prevMouseCoords, gfx::Coords& startCoords, gfx::Rectangle refRect, win::SDLRenderer* renderer) override;
		void setToolColour(const uint8_t RGBA[]) override {}
	};
}
