#include "PAINT_Program.h"
#include "SDL.h"
#include <iostream>

using namespace paint;
static Program s_program;

int main(int /*argc*/, char ** /* argv*/)
{
	// Create root window.
	const auto rootWindow = SDL_CreateWindow("rootWindow", 300, 100, 1200, 800, 0);
	const auto renderer = SDL_CreateRenderer(rootWindow, -1, SDL_RENDERER_ACCELERATED);
	const auto surface = SDL_GetWindowSurface(rootWindow);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	const auto texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 800, 1200);

	if (!rootWindow) {
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
	}

	s_program.initialize(rootWindow, renderer, surface, texture);
	s_program.run();
	SDL_DestroyWindow(rootWindow);
	SDL_Quit();

	return 0;
} 