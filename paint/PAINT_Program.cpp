#include "PAINT_pch.h"
#include "PAINT_Program.h"
#include "PAINT_DrawWindow.h"
#include "PAINT_Screen.h"
#include "WIN_Mouse.h"

using namespace paint;
using namespace gfx;
using namespace win;

using UIelementVector = std::vector<std::shared_ptr<UIelement>>;

Program::Program()
	: screen_(nullptr)
	, renderer_(nullptr)
{

}

static std::shared_ptr<UIelement> GetTopmostElement(const UIelementVector& children, const int x, const int y)
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

void Program::initialize(SDL_Renderer* renderer)
{
	renderer_ = renderer;
	auto screenRect = gfx::Rectangle(0, 0, 1200, 800);
	screen_ = std::make_shared<Screen>(renderer, screenRect, "Screen");
	
}

void Program::run() const
{
	SDL_Event e;
	auto quit = false;
	auto xMouse{ 0 };
	auto yMouse{ 0 };
	auto xPrev{ 0 };
	auto yPrev{ 0 };

	auto drawWindow = screen_->getDrawWindow();

	auto clicked = false;

	auto button = MouseButton::Left;
	
	//While application is running
	std::shared_ptr<UIelement> activeElement = nullptr;
	while (!quit) {
		auto rerenderFlag = false;

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
					if (!clicked)
					{
						if (activeElement) {
							rerenderFlag = activeElement->mouseExit(button);
						}
						activeElement = active;

						if (activeElement) {
							rerenderFlag = activeElement->mouseEnter();
						}
					}

				}

				if(activeElement){
					rerenderFlag = activeElement->mouseMove();
				}
				
			}

			// If mouse is clicked

			if (e.type == SDL_MOUSEBUTTONDOWN) {


				
				clicked = true;
				drawWindow->setStartCoord({ xMouse, yMouse });

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
					drawWindow->setMouseCoords({ xMouse, yMouse });
					drawWindow->setPrevCoords({ xPrev, yPrev });
					// ReSharper disable once CppLocalVariableMightNotBeInitialized
					activeElement->mouseButtonDown(button);
					
					rerenderFlag = activeElement->mouseButtonDown(button);
				}
				
			}

			if (e.type == SDL_MOUSEBUTTONUP) {
				clicked = false;
				if (activeElement) {
					rerenderFlag = activeElement->mouseButtonUp(button);
				}
			}

			xPrev = xMouse;
			yPrev = yMouse;

			if (rerenderFlag) {
				screen_->updateAndRerender();
			}
			
		}
		SDL_RenderPresent(renderer_);
	}
}
