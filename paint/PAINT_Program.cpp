#include "PAINT_Program.h"
#include "PAINT_DrawWindow.h"
#include "PAINT_ToolWindow.h"
#include "PAINT_StatusBarWindow.h"
#include "WIN_Button.h"
#include "WIN_Mouse.h"
#include <cassert>
#include <SDL.h>
#include <iostream>
#include "WIN_TableLayout.h"
#include <WIN_GenericBox.h>


using namespace paint;
using namespace gfx;
using namespace win;

Program::Program()
: screen_(std::make_shared<FreeLayout>(), Rectangle(300,100,1200,720),"screen")
, window_(nullptr)
, renderer_(nullptr)
, surface_(nullptr)
, texture_(nullptr)
, drawWindow_(nullptr)
{
	
}
void Program::initialize(SDL_Window* sdlWindow, SDL_Renderer* renderer, SDL_Surface* surface, SDL_Texture* texture)
{
	renderer_ = renderer;
	window_ = sdlWindow;
	surface_ = surface;
	texture_ = texture;

	// Create draw window.
	gfx::Rectangle drawRect(200, 40, 1000, 720);
	auto drawWindow = std::make_shared<DrawWindow>(sdlWindow, renderer, surface, drawRect, "drawWindow");
	const gfx::Colour drawColour{ 255, 255, 255, 255 };
	drawWindow->setBackgroundColour(drawColour);
	screen_.addChild(drawWindow);

	drawWindow_ = drawWindow;

	// Create tool window.
	gfx::Rectangle toolRect(0, 40, 200, 720);
	auto toolWindow = std::make_shared<ToolWindow>(sdlWindow, renderer, surface, toolRect, "toolWindow");
	gfx::Colour toolColour{ 59, 156, 141, 120 };
	toolWindow->setBackgroundColour(toolColour);

	// Tool window sub-containers - referring to sub-containers as 'box' to distinguish from 'window'
	// Create toolbar inside tool window, allocating 3x2 table for 6 tool elements
	gfx::Rectangle toolbarRect(10, 50, 180, 340);
	auto toolbarLayout = std::make_shared<win::TableLayout>(10, 10, 10, 10, 3, 2);
	auto toolbarBox = std::make_shared<ToolWindow>(sdlWindow, renderer, surface, toolbarRect, "toolbarBox", toolbarLayout);
	gfx::Colour toolboxColour{ 100, 255, 220, 255 };
	toolbarBox->setBackgroundColour(toolboxColour);
	// Create tool window buttons.
	gfx::Colour yellow(255, 255, 0, 255);
	for (int i = 0; i < 6; i++) {
		gfx::Rectangle rectGenericBox(0, 40, 20, 20);
		auto box = std::make_shared<GenericBox>(rectGenericBox, "genericBox", yellow, yellow, renderer);
		toolbarBox->addChild(box);
	}
	toolWindow->addChild(toolbarBox);

	// Create area for colour picker
	gfx::Rectangle colourPickerRect(10, 400, 180, 200);
	auto colourPickerBox= std::make_shared<ToolWindow>(sdlWindow, renderer, surface, colourPickerRect, "colourPickerBox");
	gfx::Colour colourPickerColour{ 150, 255, 240, 255 };
	colourPickerBox->setBackgroundColour(colourPickerColour);
	toolWindow->addChild(colourPickerBox);
	
	screen_.addChild(toolWindow);

	// Create status bar window.
	gfx::Rectangle statusRect(0, 760, 1200, 40);
	auto statusWindow = std::make_shared<StatusBarWindow>(sdlWindow, renderer, surface, statusRect, "statusWindow");
	gfx::Colour statusColour{ 40, 115, 103, 255 };
	statusWindow->setBackgroundColour(statusColour);
	screen_.addChild(statusWindow);
	
	// Set active tool to default.

	// Anything else.
}

void Program::run()
{
	SDL_Event e;
	bool quit = false;
	int xMouse{ 0 };
	int yMouse{ 0 };
	//int xOffset;
	//int yOffset;

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
					if (rect.containsPoint(xMouse, yMouse)) {
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

			MouseButton button = MouseButton::Left;
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

					//drawWindow_->addClickedPixels(xMouse, yMouse);
					
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
