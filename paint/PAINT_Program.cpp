#include "PAINT_pch.h"
#include "PAINT_Program.h"
#include "PAINT_DrawWindow.h"
#include "PAINT_Screen.h"
#include "WIN_Mouse.h"
#include "PAINT_StatusBarWindow.h"

using namespace paint;
using namespace gfx;
using namespace win;

using UIelementVector = std::vector<std::shared_ptr<UIelement>>;

Program::Program()
	: screen_(nullptr)
	, renderer_(nullptr)
	, rootWindow_(nullptr)
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

void Program::initialize(SDL_Renderer* renderer, SDL_Window* rootWindow)
{
	//Create gfx::Renderer from SDL renderer
	//renderer_ = renderer;

	renderer_ = new Renderer(renderer);
	rootWindow_ = rootWindow;
	
	auto screenRect = gfx::Rectangle(0, 0, 1200, 800);
	screen_ = std::make_shared<Screen>(renderer_, screenRect, "Screen");
}

gfx::Rectangle Program::getRootWindowRect() const
{
	int x;
	int y;
	int width;
	int height;
	SDL_GetWindowPosition(rootWindow_, &x, &y);
	SDL_GetWindowSize(rootWindow_, &width, &height);
	return { x,y,width,height };
}

void Program::run() const
{
	SDL_Event e;
	auto quit = false;
	auto xMouse{ 0 };
	auto yMouse{ 0 };
	auto xPrev{ 0 };
	auto yPrev{ 0 };
	auto xGlobal{ 0 };
	auto yGlobal{ 0 };

	gfx::Rectangle rootWindowRect_ = getRootWindowRect();
	auto insideRootWindow = true;

	auto drawWindow = screen_->getDrawWindow();

	auto clicked = false;

	auto button = MouseButton::Left;
	
	//While application is running
	std::shared_ptr<UIelement> activeElement = nullptr;
	while (!quit) {
		// if a method causes a change in the visual representation of the program, returns 'true' and calls to rerender the relevant section, else have the method return 'false'
		auto rerenderFlag = false;
		
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0) {
			SDL_RenderClear(renderer_->getRendererSDL());
			screen_->draw();

			//User requests quit
			if (e.type == SDL_QUIT) {
				quit = true;
			}

			//If the window moved
			if (e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_MOVED) {
				rootWindowRect_ = getRootWindowRect();
			}
				
			//If the mouse moved
			if (e.type == SDL_MOUSEMOTION) {
				SDL_GetMouseState(&xMouse, &yMouse);
				auto active = GetTopmostElement(screen_->getChildren(), xMouse, yMouse);

				drawWindow->setMouseCoords({ xMouse, yMouse });
				drawWindow->setPrevCoords({ xPrev, yPrev });

				//if mouse goes outside window, usually on right-hand side
				// do we want to check for this all the time, or only if it is close to the boundaries?
				SDL_GetGlobalMouseState(&xGlobal, &yGlobal);
				if (!(xGlobal >= rootWindowRect_.x && xGlobal < (rootWindowRect_.x + rootWindowRect_.width) && yGlobal >= rootWindowRect_.y && yGlobal < (rootWindowRect_.y + rootWindowRect_.height))) {
					insideRootWindow = false;
					clicked = false;
					drawWindow->setMouseCoords({ xGlobal - rootWindowRect_.x, yGlobal - rootWindowRect_.y });
					drawWindow->setPrevCoords({ xPrev, yPrev });
					if (activeElement) {
						activeElement->mouseExit(clicked);
					}
				}
				else{
					insideRootWindow = true;
				}
				
				if (activeElement != active) {
					if (activeElement && insideRootWindow) {
						rerenderFlag = activeElement->mouseExit(clicked);
					}
					
					activeElement = active;

					if (activeElement && insideRootWindow) {
						rerenderFlag = activeElement->mouseEnter(clicked);
					}
				}

				if(activeElement && insideRootWindow){
					rerenderFlag = activeElement->mouseMove(e.motion);
				}
				
			}

			// If mouse is clicked

			if (e.type == SDL_MOUSEBUTTONDOWN) {

				if (insideRootWindow) {
					clicked = true;
				}

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
				if (activeElement && insideRootWindow) {

					drawWindow->setMouseCoords({ xMouse, yMouse });
					drawWindow->setPrevCoords({ xPrev, yPrev });
					// ReSharper disable once CppLocalVariableMightNotBeInitialized
					//activeElement->mouseButtonDown(button);
					
					rerenderFlag = activeElement->mouseButtonDown(button);
				}
				
			}

			if (e.type == SDL_MOUSEBUTTONUP) {
				clicked = false;
				if (activeElement && insideRootWindow) {
					rerenderFlag = activeElement->mouseButtonUp(button);
				}
			}

			if (xPrev != xMouse) {
				xPrev = xMouse;
			}

			if (yPrev != yMouse)
			{
				yPrev = yMouse;
			}

			if (rerenderFlag) {
				screen_->updateAndRerender();
			}
			
		}

		 // Draw buttons.
		/*for (const auto& toolChild : toolChildren) {
			toolChild->draw();
		}*/

		renderer_->renderPresent();
	}
}
