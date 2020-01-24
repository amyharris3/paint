#include "PAINT_Program.h"
#include "PAINT_DrawWindow.h"
#include "PAINT_ToolWindow.h"
#include "PAINT_StatusBarWindow.h"
#include "WIN_Button.h"
#include "WIN_Mouse.h"
#include <cassert>
#include <SDL.h>
#include <iostream>
#include <memory>
#include "PAINT_ButtonFunctions.h"

using namespace paint;
using namespace gfx;
using namespace win;

using UIelementVector = std::vector<std::shared_ptr<UIelement>>;

static std::shared_ptr<UIelement> GetTopmostElement(const UIelementVector & children, int x, int y)
{
	for (const auto& child : children) {
		const auto& rect = child->getRect();
		if (rect.ContainsPoint(x, y)) {
			if (auto childContainer = std::dynamic_pointer_cast<Container>(child)) {
				// The child is a container.
				if (!childContainer->getChildren().empty()) {
					// The container has children.
					return GetTopmostElement(childContainer->getChildren(), x, y);
				}
				else {
					return child;
				}
			}
			else {
				return child;

			}
		}
	}
	return nullptr;
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
	gfx::Colour drawColour{ 255, 255, 255, 255 };
	drawWindow->setBackgroundColour(drawColour);
	screen_.AddChild(drawWindow);

	drawWindow_ = drawWindow;

	// Create tool window.
	gfx::Rectangle toolRect(0, 40, 200, 720);
	auto toolWindow = std::make_shared<ToolWindow>(sdlWindow, renderer, surface, toolRect, "toolWindow");
	gfx::Colour toolColour{ 59, 156, 141, 120 };
	toolWindow->setBackgroundColour(toolColour);
	screen_.AddChild(toolWindow);

	toolWindow_ = toolWindow;

	// Create tool window buttons. 
	gfx::Rectangle drawButtonRect(20, 60, 60, 60);
	auto drawButton = std::make_shared<Button>(renderer_, drawButtonRect, "drawButton", "button_default.png", myAction);
	//screen_.AddChild(drawButton);
	toolWindow->AddChild(drawButton);

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

	MouseButton button;

	auto children = screen_.getChildren();
	auto toolChildren = toolWindow_->getChildren();


	bool clicked = false;

	//SDL_SetRenderTarget(renderer_, texture_);

	//While application is running
	std::shared_ptr<UIelement> activeElement = nullptr;
	std::shared_ptr<UIelement> highlightedButton = nullptr;
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

				auto active = GetTopmostElement(screen_.getChildren(), xMouse, yMouse);
				if (activeElement != active) {
					if (activeElement) {
						activeElement->mouseExit();
					}

					activeElement = active;
					if (activeElement) {
						activeElement->mouseEnter();
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
				if (activeElement) {
					SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
					const int xRel = xMouse - activeElement->getRect().x;
					const int yRel = yMouse - activeElement->getRect().y;
					activeElement->mouseButtonDown(button, xRel, yRel);
				}
			}

			if (e.type == SDL_MOUSEBUTTONUP) {
				std::cout << "Mouse button up \n";
				clicked = false;
				if (activeElement) {
					activeElement->mouseButtonUp(button);
				}
			}

		}

		// Draw everything.

		for (const auto& toolChild : toolChildren) {
			toolChild->draw();
		}

		SDL_RenderPresent(renderer_);
	}

	// TODO: dispose of window_
}
