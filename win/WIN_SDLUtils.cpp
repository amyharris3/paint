#include "WIN_pch.h"
#include "WIN_SDLUtils.h"

using namespace win;

SDL_Texture* SDLUtils::loadSprite(SDL_Renderer* renderer, const char* path)
{
	//Load image at specified path
	auto* loadedSurface = IMG_Load(path);
	try {
		if (!loadedSurface) {
			std::string imgErr = "Unable to load image ";
			imgErr.append(path);
			imgErr.append("! SDL_image Error : ");
			imgErr.append(IMG_GetError());
			throw std::runtime_error(imgErr);
		}
	}
	catch (std::runtime_error & e) {
		std::cout << e.what() << '\n';
		throw;
	}
	//Create texture from surface pixels
	const auto newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
	try
	{
		if (!newTexture) {
			std::string txtErr = "Unable to create texture from ";
			txtErr.append(path);
			txtErr.append("! SDL Error : ");
			txtErr.append(SDL_GetError());
			throw std::runtime_error(txtErr);
		}
	}
	catch (std::runtime_error & e) {
		std::cout << e.what() << '\n';
		throw;
	}

	//Get rid of old loaded surface
	SDL_FreeSurface(loadedSurface);
	return newTexture;
}

std::vector<SDL_Rect> SDLUtils::handleSpriteSheet(SDL_Texture* texture)
{
	// Load sprite sheet texture

	/* Sprite should be a 2x2 grid with equal size sprites.
	   Starting top left and moving clockwise, the sprites
	   represent the mouse state as over, out, up, down. */

	assert(texture && "Texture is nullptr in WIN_SDLUtils::handleSpriteSheet.");

	std::vector<SDL_Rect> spriteClips;

	int w, h;
	SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);

	try {
		if ((w%2 != 0) || (h%2 != 0)) {
			throw std::runtime_error("Uneven number of pixels in sprite image width or height");
		}
	}
	catch (std::runtime_error & e) {
		std::cout << e.what() << '\n';
		throw;
	}
	
	//Set top left sprite
	spriteClips.push_back({ 0, 0, w/2, h/2 });

	//Set top right sprite
	spriteClips.push_back({ w/2, 0, w/2, h/2 });

	//Set bottom left sprite
	spriteClips.push_back({ 0, h/2, w/2, h/2 });

	//Set bottom right sprite
	spriteClips.push_back({ w/2, h/2, w/2, h/2 });

	return spriteClips;
}