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
		ShapeTool(gfx::Renderer* renderer);
		~ShapeTool() = default;
		ShapeTool(const ShapeTool& that) = default;
		ShapeTool(ShapeTool && that) = default;
		ShapeTool& operator=(const ShapeTool & that) = default;
		ShapeTool& operator=(ShapeTool && that) = default;

		void setActiveShape(std::shared_ptr<Shape> shape);
		std::shared_ptr<Shape> getActiveShape() const { return activeShape_; }

		void toolFunction(win::Coords& mouseCoords, win::Coords& prevMouseCoords, win::Coords& startCoords, gfx::Rectangle refRect) override;
		void toolFunctionEnd(win::Coords& mouseCoords, win::Coords& prevMouseCoords, win::Coords& startCoords, gfx::Rectangle refRect) override;

		void setToolColour(const uint8_t RGBA[]) override {}
	private:
		std::shared_ptr<Shape> activeShape_;
		gfx::Renderer* renderer_;
		uint8_t drawRGBA_[4];

	};
}
