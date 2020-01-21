#include "PAINT_Program.h"
#include <SDL.h>
//#include "SDL_ttf.h"
#include <iostream>
#include <SDL_image.h>

using namespace paint;
static Program s_program;

int main(int argc, char ** argv)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return 1;
	}
	IMG_Init(IMG_INIT_JPG);

	// Create root window.
	SDL_Window* rootWindow = SDL_CreateWindow("rootWindow", 300, 100, 1200, 800, 0);
	SDL_Renderer* renderer = SDL_CreateRenderer(rootWindow, -1, SDL_RENDERER_ACCELERATED);
	SDL_Surface* surface = SDL_GetWindowSurface(rootWindow);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 800, 1200);


	if (rootWindow == nullptr) {
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
	}

	s_program.initialize(rootWindow, renderer, surface, texture);
	s_program.run();
	if (texture) {
		SDL_DestroyTexture(texture);
		texture = nullptr;
	}
	if (renderer) {
		SDL_DestroyRenderer(renderer);
		renderer = nullptr;
	}
	if (surface) {
		SDL_FreeSurface(surface);
		surface = nullptr;
	}
	if (rootWindow) {
		SDL_DestroyWindow(rootWindow);
		rootWindow = nullptr;
	}
	IMG_Quit();
	SDL_Quit();

	return 0;
} 