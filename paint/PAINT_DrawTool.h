#pragma once
#include "PAINT_Tool.h"

struct SDL_Renderer;
struct SDL_Texture;

namespace win
{
	struct Coords;
}

namespace paint
{
	class Brush;
	class DrawWindow;
	
	class DrawTool final :
		public Tool
	{
	public:;
		DrawTool() = delete;
		DrawTool(SDL_Renderer* renderer, SDL_Texture* texture);
		virtual ~DrawTool() = default;
		DrawTool(const DrawTool& that) = default;
		DrawTool(DrawTool&& that) = default;
		DrawTool& operator=(const DrawTool& that) = default;
		DrawTool& operator=(DrawTool&& that) = default;

		void toolFunction(win::Coords mouseCoords, win::Coords prevMouseCoords, win::Coords startCoords, gfx::Rectangle refRect) override;
		void toolFunctionEnd(win::Coords mouseCoords, win::Coords prevMouseCoords, win::Coords startCoords, gfx::Rectangle refRect) override;

	private:
		SDL_Renderer* renderer_;
		SDL_Texture* texture_;
		
	};


}
