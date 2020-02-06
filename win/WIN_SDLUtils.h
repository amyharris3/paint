#pragma once

namespace win
{
	namespace SDLUtils
	{
		SDL_Texture* loadSprite(SDL_Renderer* renderer, const char* path);
		std::vector<SDL_Rect> handleSpriteSheet(SDL_Texture* texture);
	}
}

