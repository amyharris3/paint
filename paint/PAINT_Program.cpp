#include "PAINT_Program.h"
#include "PAINT_DrawWindow.h"
#include "PAINT_ToolWindow.h"
#include "PAINT_StatusBarWindow.h"
#include "PAINT_Screen.h"
#include "WIN_Button.h"
#include "WIN_Mouse.h"
#include <cassert>
#include <SDL.h>
#include <iostream>
#include <memory>
#include "PAINT_ButtonFunctions.h"
#include <WIN_GenericBox.h>
#include "WIN_TableLayout.h"
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

void Program::run()
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
	

	bool clicked = false;


	//While application is running
	std::shared_ptr<UIelement> activeElement = nullptr;
	while (!quit) {


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
						activeElement->mouseExit();
					}

					activeElement = active;
					if (activeElement) {
						activeElement->mouseEnter();
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
				if (activeElement) {
					//SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
					drawWindow->setMouseCoords({ xMouse, yMouse });
					drawWindow->setPrevCoords({ xPrev, yPrev });

					activeElement->mouseButtonDown(button);
				}
			}

			if (e.type == SDL_MOUSEBUTTONUP) {
				clicked = false;
				if (activeElement) {
					activeElement->mouseButtonUp(button);
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
