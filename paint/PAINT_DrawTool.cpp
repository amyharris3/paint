#include "PAINT_DrawTool.h"
#include "PAINT_DrawWindow.h"
#include <SDL.h>
#include "PAINT_Brush.h"
#include "WIN_Coords.h"
#include <cassert>

using namespace paint;
using namespace win;


DrawTool::DrawTool(SDL_Renderer* renderer, SDL_Texture* texture)
	: renderer_(renderer)
	, texture_(texture)
{
	// Activate a default brush
	activeBrush_ = std::make_shared<Brush>(0);
}

void DrawTool::toolFunction(win::Coords relCoords, win::Coords prevRelCoords)
{
	lines_.push_back({ relCoords.x, relCoords.y, prevRelCoords.x, prevRelCoords.y });
	SDL_SetRenderTarget(renderer_, texture_);
	renderLines();
	SDL_SetRenderTarget(renderer_, nullptr);
}

void DrawTool::renderLines()
{
	assert(activeBrush_ && "activeBrush_ is nullptr.");
	const auto thickness = activeBrush_->getThickness();
	assert((thickness == 0) || (thickness == 1) || (thickness == 2) && "brush thickness in renderLines is not 0, 1, or 2.");
	for (const auto& line : lines_) {
		SDL_RenderDrawLine(renderer_, line.x1, line.y1, line.x2, line.y2);
		for (auto sign : { -1, 1 })
		{
			if (thickness > 0) {
				for (auto thick = 0; thick <= thickness; ++thick) {
					SDL_RenderDrawLine(renderer_, line.x1 + (sign * thick), line.y1, line.x2 + (sign * thick), line.y2);
					SDL_RenderDrawLine(renderer_, line.x1, line.y1 + (sign * thick), line.x2, line.y2 + (sign * thick));
				}
			}

			if (thickness > 1) {

				SDL_RenderDrawLine(renderer_, line.x1 + (sign * 1), line.y1 + (sign * 1), line.x2 + (sign * 1), line.y2 + (sign * 1));
				SDL_RenderDrawLine(renderer_, line.x1 + (sign * 2), line.y1 + (sign * 1), line.x2 + (sign * 2), line.y2 + (sign * 1));
				SDL_RenderDrawLine(renderer_, line.x1 + (sign * 1), line.y1 + (sign * 2), line.x2 + (sign * 1), line.y2 + (sign * 2));

				SDL_RenderDrawLine(renderer_, line.x1 - (sign * 1), line.y1 + (sign * 1), line.x2 - (sign * 1), line.y2 + (sign * 1));
				SDL_RenderDrawLine(renderer_, line.x1 - (sign * 2), line.y1 + (sign * 1), line.x2 - (sign * 2), line.y2 + (sign * 1));
				SDL_RenderDrawLine(renderer_, line.x1 - (sign * 1), line.y1 + (sign * 2), line.x2 - (sign * 1), line.y2 + (sign * 2));
			}
				
		}
	}
}
