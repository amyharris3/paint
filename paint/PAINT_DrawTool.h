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
	
	class DrawTool :
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

		void toolFunction(win::Coords relCoords, win::Coords prevRelCoords) override;
		void renderLines();

	private:
		SDL_Renderer* renderer_;
		SDL_Texture* texture_;
		
	};


}
