#include "PAINT_pch.h"
#include "PAINT_Tool.h"
#include "PAINT_Brush.h"

using namespace paint;

Tool::Tool()
	: activeBrush_(nullptr)
	, drawRGBA_{255,255,255,255}
{
}

void Tool::setActiveBrush(std::shared_ptr<Brush> brush)
{
	activeBrush_ = std::move(brush);
}

void Tool::clearLines()
{
	lines_.clear();
}

void Tool::setALine(gfx::Line const line)
{
	lines_.push_back(line);
}

void Tool::setLines(std::vector<gfx::Line> lines)
{
	lines_ = std::move(lines);
}

void Tool::setToolColour(const uint8_t RGBA[])
{
	for (auto i = 0; i < 4; i++) {
		drawRGBA_[i] = RGBA[i];
	}
}

//
//
//void Tool::renderLines(gfx::Renderer* renderer, const std::vector<gfx::Line>& lines) const
//{
//	assert(activeBrush_ && "activeBrush_ is nullptr.");
//	const auto thickness = activeBrush_->getThickness();
//	assert((thickness == 0) || (thickness == 1) || (thickness == 2) && "brush thickness in renderLines is not 0, 1, or 2.");
//	for (const auto& line : lines) {
//		SDL_RenderDrawLine(renderer, line.x1, line.y1, line.x2, line.y2);
//		for (auto sign : { -1, 1 }) {
//			if (thickness > 0) {
//				for (auto thick = 0; thick <= thickness; ++thick) {
//					SDL_RenderDrawLine(renderer, line.x1 + (sign * thick), line.y1, line.x2 + (sign * thick), line.y2);
//					SDL_RenderDrawLine(renderer, line.x1, line.y1 + (sign * thick), line.x2, line.y2 + (sign * thick));
//				}
//			}
//
//			if (thickness > 1) {
//
//				SDL_RenderDrawLine(renderer, line.x1 + (sign * 1), line.y1 + (sign * 1), line.x2 + (sign * 1), line.y2 + (sign * 1));
//				SDL_RenderDrawLine(renderer, line.x1 + (sign * 2), line.y1 + (sign * 1), line.x2 + (sign * 2), line.y2 + (sign * 1));
//				SDL_RenderDrawLine(renderer, line.x1 + (sign * 1), line.y1 + (sign * 2), line.x2 + (sign * 1), line.y2 + (sign * 2));
//
//				SDL_RenderDrawLine(renderer, line.x1 - (sign * 1), line.y1 + (sign * 1), line.x2 - (sign * 1), line.y2 + (sign * 1));
//				SDL_RenderDrawLine(renderer, line.x1 - (sign * 2), line.y1 + (sign * 1), line.x2 - (sign * 2), line.y2 + (sign * 1));
//				SDL_RenderDrawLine(renderer, line.x1 - (sign * 1), line.y1 + (sign * 2), line.x2 - (sign * 1), line.y2 + (sign * 2));
//			}
//
//		}
//	}
//}
//
//
