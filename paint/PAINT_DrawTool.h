#pragma once
#include "PAINT_Tool.h"
#include <vector>

struct SDL_Renderer;
struct SDL_Texture;

namespace paint
{
	class Brush;
	struct Coords;
	class DrawWindow;



	
	class DrawTool :
		public Tool
	{
	public:;
		DrawTool() = default;
		DrawTool(SDL_Renderer* renderer, SDL_Texture* texture);
		virtual ~DrawTool() = default;
		DrawTool(const DrawTool& that) = default;
		DrawTool(DrawTool&& that) = default;
		DrawTool& operator=(const DrawTool& that) = default;
		DrawTool& operator=(DrawTool&& that) = default;

		void toolFunction(Coords mouseCoords, Coords prevMouseCoords) override;
		void renderLines();
		void clearLines();
		//void writeToTexture() override;

	private:
		SDL_Renderer* renderer_;
		SDL_Texture* texture_;
	};


}
