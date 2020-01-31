#include "WIN_ButtonUtils.h"
#include <SDL.h>
#include <SDL_image.h>
#include <cstdio>
#include <cassert>

using namespace win;

SDL_Texture* ButtonUtils::loadSprite(SDL_Renderer* renderer, const char* path)
{
	//The final texture
	SDL_Texture* newTexture = nullptr;

	//Load image at specified path
	auto* loadedSurface = IMG_Load(path);
	if (loadedSurface == nullptr) {
		printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
	}
	else {
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == nullptr) {
			printf("Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
		}
		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}
	return newTexture;
}

std::vector<SDL_Rect> ButtonUtils::handleSpriteSheet(SDL_Texture* texture)
{
	//Load sprite sheet texture
	assert(texture);
	std::vector<SDL_Rect> spriteClips;
	
	//Set top left sprite
	spriteClips.push_back({ 0, 0, 100, 100 });

	//Set top right sprite
	spriteClips.push_back({ 100, 0, 100, 100 });

	//Set bottom left sprite
	spriteClips.push_back({ 0, 100, 100, 100 });

	//Set bottom right sprite
	spriteClips.push_back({ 100, 100, 100, 100 });

	return spriteClips;
}