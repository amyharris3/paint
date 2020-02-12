#pragma once
#include "PAINT_Tool.h"
#include "PAINT_Shape.h"
#include "GFX_Renderer.h"

namespace paint
{
	class Shape;
	
	class ShapeTool final :
		public Tool
	{
	public:
		ShapeTool() = delete;
		ShapeTool(gfx::Colour colour);
		~ShapeTool() = default;
		ShapeTool(const ShapeTool& that) = default;
		ShapeTool(ShapeTool && that) = default;
		ShapeTool& operator=(const ShapeTool & that) = default;
		ShapeTool& operator=(ShapeTool && that) = default;

		void setActiveShape(std::shared_ptr<Shape> shape);
		std::shared_ptr<Shape> getActiveShape() const { return activeShape_; }

		void toolFunction(gfx::Coords& mouseCoords, gfx::Coords& prevMouseCoords, gfx::Coords& startCoords, gfx::Rectangle refRect, win::SDLRenderer* renderer) override;
		void toolFunctionEnd(gfx::Coords& mouseCoords, gfx::Coords& prevMouseCoords, gfx::Coords& startCoords, gfx::Rectangle refRect, win::SDLRenderer* renderer) override;

		void setToolColour(const uint8_t RGBA[]) override {}
	private:
		std::shared_ptr<Shape> activeShape_;
		uint8_t drawRGBA_[4];

	};
}
