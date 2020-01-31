#pragma once
#include <SDL.h>
#include <vector>

namespace win
{
	namespace ButtonUtils
	{
		SDL_Texture* loadSprite(SDL_Renderer* renderer, const char* path);
		std::vector<SDL_Rect> handleSpriteSheet(SDL_Texture* texture);
	}
}

