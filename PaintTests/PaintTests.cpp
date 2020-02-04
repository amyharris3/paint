#include "pch.h"
#include "../SDL/include/SDL.h"
#include "CppUnitTest.h"
#include "../paint/PAINT_DrawWindow.h"
#include <memory>
#include "../paint/PAINT_Brush.h"
#include "../paint/PAINT_Brush.cpp"
#include "WIN_Button.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace gfx;
using namespace win;
using namespace paint;

namespace PaintTests
{
	
	//TEST_CLASS(TestPaintTestElement)
	//{
	//public:

	//	TEST_METHOD(TestDrawWindowColourSwap)
	//	{
	//		/*const auto testWindow = SDL_CreateWindow("rootWindow", 300, 100, 1200, 800, 0);
	//		const auto renderer = SDL_CreateRenderer(testWindow, -1, SDL_RENDERER_ACCELERATED);
	//		const auto surface = SDL_GetWindowSurface(testWindow);

	//		gfx::Rectangle drawRect(200, 40, 1000, 720);
	//		auto drawWindow = std::make_shared<DrawWindow>(testWindow, renderer, surface, drawRect, "drawWindow");
	//		//auto drawWindow = std::make_shared<DrawWindow>(testWindow, renderer, surface, drawRect, "drawWindow");
	//		//const gfx::Colour drawColour{ 255, 255, 255, 255 };
	//		//drawWindow->setBackgroundColour(drawColour);


	//		SDL_DestroyWindow(testWindow);
	//		*/
	//	}
	//};

	TEST_CLASS(TestPaintBrush)
	{
	public:

		TEST_METHOD(TestConstructionInvariant)
		{
			const Brush brush(1);
			//Assert::AreEqual(brush.getThickness(), 7);
		}

		TEST_METHOD(TestCopyConstruction)
		{
			const Brush a(2);
			const Brush b(a);
			Assert::AreEqual(b.getThickness(), 2);
		}

		TEST_METHOD(TestAssignmentOperator)
		{
			const Brush a(1);
			const Brush b = a;
			Assert::AreEqual(b.getThickness(), 1);
		}

		TEST_METHOD(TestSetThickness)
		{
			Brush a(0);
			a.setThickness(2);
			Assert::AreEqual(a.getThickness(), 2);
		}

		TEST_METHOD(TestGetThickness)
		{
			const Brush a(0);
			const auto thickness = a.getThickness();
			Assert::AreEqual(thickness, 0);
		}

		TEST_METHOD(TestChangingThicknessOutOfBounds)
		{
			Assert::ExpectException<std::runtime_error>(
				[]() {
					Brush a(0);
					a.setThickness(-3);
				});
		}

	};
}