#pragma once
#include <iostream>
#include <vector>

struct SDL_Renderer;
struct SDL_Texture;

namespace paint
{
	class Brush;
	struct Coords;
	struct Line
	{
		int x1;
		int y1;
		int x2;
		int y2;

	};
	class Tool
	{
	public:
		Tool();
		virtual ~Tool() = default;
		Tool(const Tool& that) = default;
		Tool(Tool && that) = default;
		Tool& operator=(const Tool & that) = default;
		Tool& operator=(Tool && that) = default;

		void setActiveBrush(std::shared_ptr<Brush> brush);
		void clearLines();
		virtual void toolFunction(Coords mouseCoords, Coords prevMouseCoords) = 0;
		//virtual void writeToTexture() = 0;
		
	private:
		std::shared_ptr<Brush> activeBrush_;


	protected:
		std::vector<Line> lines_;
		
	};
}
