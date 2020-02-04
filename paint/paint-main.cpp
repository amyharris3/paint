#include "PAINT_Program.h"
#include <SDL.h>
#include <iostream>
#include <SDL_image.h>



using namespace paint;
static Program s_program;

int main(int /*argc*/, char ** /* argv*/)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return 1;
	}
	IMG_Init(IMG_INIT_JPG);

	// Create root window.
	auto rootWindow = SDL_CreateWindow("rootWindow", 300, 100, 1200, 800, 0);
	auto renderer = SDL_CreateRenderer(rootWindow, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	if (!rootWindow) {
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
	}

	s_program.initialize(renderer);
	s_program.run();

	if (renderer) {
		SDL_DestroyRenderer(renderer);
		renderer = nullptr;
	}

	if (rootWindow) {
		SDL_DestroyWindow(rootWindow);
		rootWindow = nullptr;
	}
	IMG_Quit();
	SDL_Quit();

	return 0;
} 