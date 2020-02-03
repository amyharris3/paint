#include "PAINT_Program.h"
#include "PAINT_DrawWindow.h"
#include "PAINT_ToolWindow.h"
#include "PAINT_Screen.h"
#include "WIN_Mouse.h"
#include <cassert>
#include <SDL.h>
#include <iostream>
#include <memory>
#include "PAINT_ColourPicker.h"


using namespace paint;
using namespace gfx;
using namespace win;

using UIelementVector = std::vector<std::shared_ptr<UIelement>>;

static std::shared_ptr<UIelement> GetTopmostElement(const UIelementVector& children, int x, int y)
{
	for (const auto& child : children) {
		const auto& rect = child->getRect();
		if (rect.containsPoint(x, y)) {
			if (const auto childContainer = std::dynamic_pointer_cast<Container>(child)) {
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

Program::Program()
	: screen_(nullptr)
	, renderer_(nullptr)
{
	
}

void Program::initialize(SDL_Renderer* renderer)
{
	renderer_ = renderer;
	auto screenRect = gfx::Rectangle(0, 0, 1200, 800);
	screen_ = std::make_shared<Screen>(renderer, screenRect, "Screen");
	
}

void Program::run() const
{
	SDL_Event e;
	bool quit = false;
	int xMouse{ 0 };
	int yMouse{ 0 };
	int xPrev{ 0 };
	int yPrev{ 0 };

	auto children = screen_->getChildren();
	auto toolChildren = screen_->getToolWindow()->getChildren();
	auto drawWindow = screen_->getDrawWindow();


	auto clicked = false;

	// if a method causes a change in the visual representation of the program, returns 'true' and calls to rerender the relevant section, else have the method return 'false'
	auto rerender = false;

	//While application is running
	std::shared_ptr<UIelement> activeElement = nullptr;
	while (!quit) {
		rerender = false;

		//Handle events on queue
		while (SDL_PollEvent(&e) != 0) {
			SDL_RenderClear(renderer_);
			screen_->draw();

			//User requests quit
			if (e.type == SDL_QUIT) {
				quit = true;
			}

			//If the mouse moved
			if (e.type == SDL_MOUSEMOTION) {

				SDL_GetMouseState(&xMouse, &yMouse);
				
				auto active = GetTopmostElement(screen_->getChildren(), xMouse, yMouse);
				if (activeElement != active) {
					if (activeElement) {
						rerender = activeElement->mouseExit();
					}

					activeElement = active;
					
					if (activeElement) {
						rerender = activeElement->mouseEnter();
					}
				}

				if(activeElement){
					rerender = activeElement->mouseMove();
				}
				if (rerender) {
					screen_->updateAndRerender();
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
				if (activeElement) {
					//SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
					drawWindow->setMouseCoords({ xMouse, yMouse });
					drawWindow->setPrevCoords({ xPrev, yPrev });
					
					rerender = activeElement->mouseButtonDown(button);
				}

				if (rerender) {
					screen_->updateAndRerender();
				}
				
			}

			if (e.type == SDL_MOUSEBUTTONUP) {
				std::cout << "Mouse button up \n";
				clicked = false;
				if (activeElement) {
					rerender = activeElement->mouseButtonUp(button);
				}
				if (rerender) {
					screen_->updateAndRerender();
				}
			}

			if (xPrev != xMouse) {
				xPrev = xMouse;
			}

			if (yPrev != yMouse)
			{
				yPrev = yMouse;
			}

		}

		 // Draw buttons.
		/*for (const auto& toolChild : toolChildren) {
			toolChild->draw();
		}*/



		SDL_RenderPresent(renderer_);
	}

}
