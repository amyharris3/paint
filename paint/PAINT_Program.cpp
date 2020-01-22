#include "PAINT_Program.h"
#include "PAINT_DrawWindow.h"
#include "PAINT_ToolWindow.h"
#include "PAINT_StatusBarWindow.h"
#include "WIN_Mouse.h"
#include <cassert>
#include <SDL.h>
#include <iostream>

using namespace paint;
using namespace gfx;
using namespace win;

void Program::initialize(SDL_Window* sdlWindow, SDL_Renderer* renderer, SDL_Surface* surface, SDL_Texture* texture)
{
	renderer_ = renderer;
	window_ = sdlWindow;
	surface_ = surface;
	texture_ = texture;

	// Create draw window.
	gfx::Rectangle drawRect(200, 40, 1000, 720);
	auto drawWindow = std::make_shared<DrawWindow>(sdlWindow, renderer, surface, drawRect, "drawWindow");
	gfx::Colour drawColour{ 255, 255, 255, 255 };
	drawWindow->setBackgroundColour(drawColour);
	screen_.AddChild(drawWindow);

	drawWindow_ = drawWindow;

	// Create tool window.
	gfx::Rectangle toolRect(0, 40, 200, 720);
	//TableLayout toolLayout(10, 10, 5, 5, 10, 10, 3, 2);
	auto toolWindow = std::make_shared<ToolWindow>(sdlWindow, renderer, surface, toolRect, "toolWindow");
	gfx::Colour toolColour{ 59, 156, 141, 120 };
	toolWindow->setBackgroundColour(toolColour);
	screen_.AddChild(toolWindow);

	// Create status bar window.
	gfx::Rectangle statusRect(0, 760, 1200, 40);
	auto statusWindow = std::make_shared<StatusBarWindow>(sdlWindow, renderer, surface, statusRect, "statusWindow");
	gfx::Colour statusColour{ 40, 115, 103, 255 };
	statusWindow->setBackgroundColour(statusColour);
	screen_.AddChild(statusWindow);

	// Set active tool to default.

	// Anything else.
}

void Program::run()
{
	SDL_Event e;
	bool quit = false;
	int xMouse{ 0 };
	int yMouse{ 0 };
	int xOffset;
	int yOffset;

	MouseButton button;

	auto children = screen_.getChildren();

	bool clicked = false;

	//SDL_SetRenderTarget(renderer_, texture_);

	//While application is running
	std::shared_ptr<UIelement> activeElement = nullptr;
	while (!quit) {


		//Handle events on queue
		while (SDL_PollEvent(&e) != 0) {
			SDL_RenderClear(renderer_);
			screen_.draw();

			//User requests quit
			if (e.type == SDL_QUIT) {
				quit = true;
			}

			//If the mouse moved
			if (e.type == SDL_MOUSEMOTION) {

				SDL_GetMouseState(&xMouse, &yMouse);
				//Get the mouse offsets
				//xOffset = e.motion.x;
				//yOffset = e.motion.y;

				for (const auto &child : children) {
					//	//If the mouse is over the child
					const Rectangle& rect = child->getRect();
					if (rect.ContainsPoint(xMouse, yMouse)) {
						//std::cout << "Its inside the window \n";
						if (activeElement != (child)) {
							if (activeElement) {
								activeElement->mouseExit();
							}
							if (child) {
								child->mouseEnter();
							}
							activeElement = (child);
						}
					}
				}
			}

			if (e.type == SDL_MOUSEBUTTONDOWN) {
				
				clicked = true;

				switch (e.button.button) {
				case SDL_BUTTON_LEFT:
					button = MouseButton::Left;
					break;

				case SDL_BUTTON_MIDDLE:
					button = MouseButton::Centre;
					break;

				case SDL_BUTTON_RIGHT:
					button = MouseButton::Right;
					break;

				default:
					assert(false);
					break;
				}

			}

			if (clicked) {
				if (activeElement == drawWindow_) {

					SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);

					//drawWindow_->AddClickedPixels(xMouse, yMouse);
					
					const int xRel = xMouse - activeElement->getRect().x;
					const int yRel = yMouse - activeElement->getRect().y;
					activeElement->mouseButtonDown(button, xRel, yRel);
				}
			}

			if (e.type == SDL_MOUSEBUTTONUP) {
				std::cout << "Mouse button up \n";
				clicked = false;
				//drawWindow_->setColor(surface);
			}

		}

		// Has mouse moved? No => nothing to do.
		// If so: what is the active UIelement?
		// Is it the same as before? => Nothing to do.
		// Signal to the old active one the mouse has moved out.
		// Signal to the new active one the mouse has moved in.

		// Draw everything.


		SDL_RenderPresent(renderer_);
	}

	// TODO: dispose of window_
}
