#include "PAINT_DrawTool.h"
#include "PAINT_DrawWindow.h"
#include <SDL.h>

using namespace paint;


DrawTool::DrawTool(SDL_Renderer* renderer, SDL_Texture* texture)
	: renderer_(renderer)
	, texture_(texture)
{
}

void DrawTool::toolFunction(Coords relCoords, Coords prevRelCoords)
{

	lines_.push_back({ relCoords.x, relCoords.y, prevRelCoords.x, prevRelCoords.y });
	SDL_SetRenderTarget(renderer_, texture_);
	renderLines();
	SDL_SetRenderTarget(renderer_, NULL);
}

void DrawTool::renderLines()
{
	int thickness = 2;
	for (const auto& line : lines_) {

		//for (std::vector<Line>::const_iterator i = lines_.begin(); i != lines_.end(); ++i) {
			//Line line = *i;
		SDL_RenderDrawLine(renderer_, line.x1, line.y1, line.x2, line.y2);
		if (thickness > 0) {
			for (auto thick = 0; thick <= thickness; ++thick) {
				SDL_RenderDrawLine(renderer_, line.x1 - thick, line.y1, line.x2 - thick, line.y2);
				SDL_RenderDrawLine(renderer_, line.x1 + thick, line.y1, line.x2 + thick, line.y2);
				SDL_RenderDrawLine(renderer_, line.x1, line.y1 - thick, line.x2, line.y2 - thick);
				SDL_RenderDrawLine(renderer_, line.x1, line.y1 + thick, line.x2, line.y2 + thick);
			}

			if (thickness > 1) {
				SDL_RenderDrawLine(renderer_, line.x1 + 1, line.y1 + 1, line.x2 + 1, line.y2 + 1);
				SDL_RenderDrawLine(renderer_, line.x1 + 2, line.y1 + 1, line.x2 + 2, line.y2 + 1);
				SDL_RenderDrawLine(renderer_, line.x1 + 1, line.y1 + 2, line.x2 + 1, line.y2 + 2);

				SDL_RenderDrawLine(renderer_, line.x1 - 1, line.y1 - 1, line.x2 - 1, line.y2 - 1);
				SDL_RenderDrawLine(renderer_, line.x1 - 2, line.y1 - 1, line.x2 - 2, line.y2 - 1);
				SDL_RenderDrawLine(renderer_, line.x1 - 1, line.y1 - 2, line.x2 - 1, line.y2 - 2);

				SDL_RenderDrawLine(renderer_, line.x1 - 1, line.y1 + 1, line.x2 - 1, line.y2 + 1);
				SDL_RenderDrawLine(renderer_, line.x1 - 2, line.y1 + 1, line.x2 - 2, line.y2 + 1);
				SDL_RenderDrawLine(renderer_, line.x1 - 1, line.y1 + 2, line.x2 - 1, line.y2 + 2);

				SDL_RenderDrawLine(renderer_, line.x1 + 1, line.y1 - 1, line.x2 + 1, line.y2 - 1);
				SDL_RenderDrawLine(renderer_, line.x1 + 2, line.y1 - 1, line.x2 + 2, line.y2 - 1);
				SDL_RenderDrawLine(renderer_, line.x1 + 1, line.y1 - 2, line.x2 + 1, line.y2 - 2);
			}
		}
	}
}

//void DrawTool::writeToTexture()
//{
//	
//	//SDL_SetRenderTarget(renderer_, texture_);
//	//renderLines();
//	////SDL_GetRenderTarget(renderer_);
//	//SDL_SetRenderTarget(renderer_, NULL);
//
//}


