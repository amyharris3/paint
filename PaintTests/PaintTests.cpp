#include "pch.h"
#include "../SDL/include/SDL.h"
#include "CppUnitTest.h"
#include "../paint/PAINT_DrawWindow.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace gfx;
using namespace win;
using namespace paint;

namespace PaintTests
{
	
	TEST_CLASS(TestPaintTestElement)
	{
	public:

		TEST_METHOD(TestDrawWindowColourSwap)
		{
			/*const auto testWindow = SDL_CreateWindow("rootWindow", 300, 100, 1200, 800, 0);
			const auto renderer = SDL_CreateRenderer(testWindow, -1, SDL_RENDERER_ACCELERATED);
			const auto surface = SDL_GetWindowSurface(testWindow);
			
			gfx::Rectangle drawRect(200, 40, 1000, 720);
			auto drawWindow = std::make_shared<DrawWindow>(testWindow, renderer, surface, drawRect, "drawWindow");
			//auto drawWindow = std::make_shared<DrawWindow>(testWindow, renderer, surface, drawRect, "drawWindow");
			//const gfx::Colour drawColour{ 255, 255, 255, 255 };
			//drawWindow->setBackgroundColour(drawColour);
			

			SDL_DestroyWindow(testWindow);
			*/
		}
		
	};
}