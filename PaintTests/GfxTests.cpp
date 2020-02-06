#include "pch.h"
#include "CppUnitTest.h"
#include "../gfx/GFX_Rectangle.h"
#include "../gfx/GFX_Colour.h"
#include "GFX_Text.h"
#include "SDL.h"
#include "SDL_ttf.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace gfx;

namespace PaintTests
{
	TEST_CLASS(TestGfxRectangles)
	{
	public:
		
		TEST_METHOD(TestDefaultConstructionInvariant)
		{
			const Rectangle rect;
			Assert::AreEqual(rect.x, 0);
			Assert::AreEqual(rect.y, 0);
			Assert::AreEqual(rect.width, 1);
			Assert::AreEqual(rect.height, 1);
		}

		TEST_METHOD(TestConstructionInvariant)
		{
			const Rectangle rect(-1, -1, 10, 10);
			Assert::AreEqual(rect.x, -1);
			Assert::AreEqual(rect.y, -1);
			Assert::AreEqual(rect.width, 10);
			Assert::AreEqual(rect.height, 10);
		}

		TEST_METHOD(TestCopyConstruction)
		{
			const Rectangle a;
			const Rectangle b(a);
			Assert::AreEqual(b.x, 0);
			Assert::AreEqual(b.y, 0);
			Assert::AreEqual(b.width, 1);
			Assert::AreEqual(b.height, 1);
		}

		TEST_METHOD(TestAssignmentOperator)
		{
			const Rectangle a;
			const Rectangle b = a;
			Assert::AreEqual(b.x, 0);
			Assert::AreEqual(b.y, 0);
			Assert::AreEqual(b.width, 1);
			Assert::AreEqual(b.height, 1);
		}

		TEST_METHOD(TestMoveConstructor)
		{
			const Rectangle rect(makeUnitRectangle());
			Assert::AreEqual(rect.x, 0);
			Assert::AreEqual(rect.y, 0);
			Assert::AreEqual(rect.width, 1);
			Assert::AreEqual(rect.height, 1);
		}

		TEST_METHOD(TestMoveAssignmentOperator)
		{
			const Rectangle rect = makeUnitRectangle();
			Assert::AreEqual(rect.x, 0);
			Assert::AreEqual(rect.y, 0);
			Assert::AreEqual(rect.width, 1);
			Assert::AreEqual(rect.height, 1);
		}

		TEST_METHOD(TestContainsPointSucceedsForInternalPoint)
		{
			const Rectangle rect(0, 0, 10, 10);
			Assert::IsTrue(rect.containsPoint(5,5));
		}

		TEST_METHOD(TestContainsPointsFailsForExternalPoint)
		{
			const Rectangle rect(0, 0, 10, 10);
			Assert::IsFalse(rect.containsPoint(20, 20));
		}

		TEST_METHOD(TestContainsPointIsInclusiveLeft)
		{
			const Rectangle rect(0, 0, 10, 10);
			Assert::IsTrue(rect.containsPoint(0, 1));
		}

		TEST_METHOD(TestContainsPointIsInclusiveTop)
		{
			const Rectangle rect(0, 0, 10, 10);
			Assert::IsTrue(rect.containsPoint(1, 0));
		}

		TEST_METHOD(TestContainsPointIsExclusiveRight)
		{
			const Rectangle rect(0, 0, 10, 10);
			Assert::IsFalse(rect.containsPoint(0, 10));
		}

		TEST_METHOD(TestContainsPointIsExclusiveBottom)
		{
			const Rectangle rect(0, 0, 10, 10);
			Assert::IsFalse(rect.containsPoint(1, 10));
		}

	private:
		static Rectangle makeUnitRectangle()
		{
			return {};
		}
	};

	TEST_CLASS(TestGfxColour)
	{
	public:

		TEST_METHOD(TestDefaultConstructor)
		{
			const Colour c(10, 20, 30, 40);
			uint8_t rgba[4];
			c.getComponents(rgba);
			Assert::AreEqual(rgba[0], static_cast<uint8_t>(10));
			Assert::AreEqual(rgba[1], static_cast<uint8_t>(20));
			Assert::AreEqual(rgba[2], static_cast<uint8_t>(30));
			Assert::AreEqual(rgba[3], static_cast<uint8_t>(40));
		}
		TEST_METHOD(TestCopyConstruction)
		{
			const Colour c1(10, 20, 30, 40);
			const auto c2(c1);
			uint8_t rgba[4];
			c2.getComponents(rgba);
			Assert::AreEqual(rgba[0], static_cast<uint8_t>(10));
			Assert::AreEqual(rgba[1], static_cast<uint8_t>(20));
			Assert::AreEqual(rgba[2], static_cast<uint8_t>(30));
			Assert::AreEqual(rgba[3], static_cast<uint8_t>(40));
		}

		TEST_METHOD(TestAsssignmentOperator)
		{
			const  Colour c1(10, 20, 30, 40);
			const auto c2 = c1;
			uint8_t rgba[4];
			c2.getComponents(rgba);
			Assert::AreEqual(rgba[0], static_cast<uint8_t>(10));
			Assert::AreEqual(rgba[1], static_cast<uint8_t>(20));
			Assert::AreEqual(rgba[2], static_cast<uint8_t>(30));
			Assert::AreEqual(rgba[3], static_cast<uint8_t>(40));
		}

		TEST_METHOD(TestMoveConstructor)
		{
			const auto c(makeWhite());
			uint8_t rgba[4];
			c.getComponents(rgba);
			Assert::AreEqual(rgba[0], static_cast<uint8_t>(255));
			Assert::AreEqual(rgba[1], static_cast<uint8_t>(255));
			Assert::AreEqual(rgba[2], static_cast<uint8_t>(255));
			Assert::AreEqual(rgba[3], static_cast<uint8_t>(255));
		}

		TEST_METHOD(TestMoveAssignmentOperator)
		{
			const auto c = makeWhite();
			uint8_t rgba[4];
			c.getComponents(rgba);
			Assert::AreEqual(rgba[0], static_cast<uint8_t>(255));
			Assert::AreEqual(rgba[1], static_cast<uint8_t>(255));
			Assert::AreEqual(rgba[2], static_cast<uint8_t>(255));
			Assert::AreEqual(rgba[3], static_cast<uint8_t>(255));
		}

		TEST_METHOD(TestGetComponents)
		{
			const Colour c(10, 20, 30, 40);
			uint8_t rgba[4];
			c.getComponents(rgba);
			Assert::AreEqual(rgba[0], static_cast<uint8_t>(10));
			Assert::AreEqual(rgba[1], static_cast<uint8_t>(20));
			Assert::AreEqual(rgba[2], static_cast<uint8_t>(30));
			Assert::AreEqual(rgba[3], static_cast<uint8_t>(40));
		}

	private:
		static Colour makeWhite()
		{
			return {255, 255, 255, 255};
		}
	};

	TEST_CLASS(TestGfxText)
	{

		TEST_METHOD(TestDefaultConstructor)
		{
			Assert::AreNotEqual(SDL_Init(SDL_INIT_VIDEO), -1);
			Assert::AreNotEqual(TTF_Init(), -1);

			Text text;

			Assert::AreEqual(text.getString().c_str(), "");
			
			Assert::AreEqual(text.getTextSize(), 12);
			Assert::IsNotNull(text.getFont());
			
			uint8_t rgba[4];
			text.getColour().getComponents(rgba);
			Assert::AreEqual(rgba[0], static_cast<uint8_t>(0));
			Assert::AreEqual(rgba[1], static_cast<uint8_t>(0));
			Assert::AreEqual(rgba[2], static_cast<uint8_t>(0));
			Assert::AreEqual(rgba[3], static_cast<uint8_t>(255));

			Assert::AreEqual(text.getWidth(), 0);
		}

		TEST_METHOD(TestExampleConstructor)
		{
			Assert::AreNotEqual(SDL_Init(SDL_INIT_VIDEO), -1);
			Assert::AreNotEqual(TTF_Init(), -1);

			Text text({10,20,30,40}, "OpenSans-Regular.ttf", 20, "Example");

			Assert::AreEqual(text.getString().c_str(), "Example");
			
			Assert::AreEqual(text.getTextSize(), 20);
			Assert::IsNotNull(text.getFont());

			uint8_t rgba[4];
			text.getColour().getComponents(rgba);
			Assert::AreEqual(rgba[0], static_cast<uint8_t>(10));
			Assert::AreEqual(rgba[1], static_cast<uint8_t>(20));
			Assert::AreEqual(rgba[2], static_cast<uint8_t>(30));
			Assert::AreEqual(rgba[3], static_cast<uint8_t>(40));

			Assert::AreNotEqual(text.getWidth(), 0);
			Assert::AreNotEqual(text.getHeight(), 0);
		}

		TEST_METHOD(TestCopyConstruction)
		{
			Assert::AreNotEqual(SDL_Init(SDL_INIT_VIDEO), -1);
			Assert::AreNotEqual(TTF_Init(), -1);
			
			Text a;
			Text b(a);
			Assert::AreEqual(a.getString(), b.getString());
			Assert::AreEqual(a.getTextSize(), b.getTextSize());
			Assert::IsNotNull(a.getFont());
			Assert::IsNotNull(b.getFont());
			Assert::IsTrue(a.getFont() == b.getFont());
			Assert::AreEqual(a.getWidth(), b.getWidth());
			Assert::AreEqual(a.getHeight(), b.getHeight());

			uint8_t rgba_a[4];
			a.getColour().getComponents(rgba_a);
			uint8_t rgba_b[4];
			b.getColour().getComponents(rgba_b);
			Assert::AreEqual(rgba_a[0], rgba_a[0]);
			Assert::AreEqual(rgba_a[1], rgba_a[1]);
			Assert::AreEqual(rgba_a[2], rgba_a[2]);
			Assert::AreEqual(rgba_a[3], rgba_a[3]);
			
		}

		TEST_METHOD(TestAssignmentOperator)
		{
			Assert::AreNotEqual(SDL_Init(SDL_INIT_VIDEO), -1);
			Assert::AreNotEqual(TTF_Init(), -1);
			
			Text a;
			Text b = a;
			Assert::AreEqual(a.getString(), b.getString());
			Assert::AreEqual(a.getTextSize(), b.getTextSize());
			Assert::IsNotNull(a.getFont());
			Assert::IsNotNull(b.getFont());
			Assert::IsTrue(a.getFont() == b.getFont());
			Assert::AreEqual(a.getWidth(), b.getWidth());
			Assert::AreEqual(a.getHeight(), b.getHeight());
			
			uint8_t rgba_a[4];
			a.getColour().getComponents(rgba_a);
			uint8_t rgba_b[4];
			b.getColour().getComponents(rgba_b);
			Assert::AreEqual(rgba_a[0], rgba_a[0]);
			Assert::AreEqual(rgba_a[1], rgba_a[1]);
			Assert::AreEqual(rgba_a[2], rgba_a[2]);
			Assert::AreEqual(rgba_a[3], rgba_a[3]);
		}

		TEST_METHOD(TestMoveConstructor)
		{
			Assert::AreNotEqual(SDL_Init(SDL_INIT_VIDEO), -1);
			Assert::AreNotEqual(TTF_Init(), -1);
			
			Text text(makeEmptyText());
			Assert::AreEqual(text.getString().c_str(), "");

			Assert::AreEqual(text.getTextSize(), 12);
			Assert::IsNotNull(text.getFont());

			uint8_t rgba[4];
			text.getColour().getComponents(rgba);
			Assert::AreEqual(rgba[0], static_cast<uint8_t>(0));
			Assert::AreEqual(rgba[1], static_cast<uint8_t>(0));
			Assert::AreEqual(rgba[2], static_cast<uint8_t>(0));
			Assert::AreEqual(rgba[3], static_cast<uint8_t>(255));

			Assert::AreEqual(text.getWidth(), 0);
		}

		TEST_METHOD(TestMoveAssignmentOperator)
		{
			Assert::AreNotEqual(SDL_Init(SDL_INIT_VIDEO), -1);
			Assert::AreNotEqual(TTF_Init(), -1);
			
			Text text = makeEmptyText();
			Assert::AreEqual(text.getString().c_str(), "");

			Assert::AreEqual(text.getTextSize(), 12);
			Assert::IsNotNull(text.getFont());

			uint8_t rgba[4];
			text.getColour().getComponents(rgba);
			Assert::AreEqual(rgba[0], static_cast<uint8_t>(0));
			Assert::AreEqual(rgba[1], static_cast<uint8_t>(0));
			Assert::AreEqual(rgba[2], static_cast<uint8_t>(0));
			Assert::AreEqual(rgba[3], static_cast<uint8_t>(255));

			Assert::AreEqual(text.getWidth(), 0);
		}

		
		TEST_METHOD(TestChangeString)
		{
			Assert::AreNotEqual(SDL_Init(SDL_INIT_VIDEO), -1);
			Assert::AreNotEqual(TTF_Init(), -1);

			Text text;
			text.changeString("NewExampleText");
			Assert::AreEqual(text.getString().c_str(), "NewExampleText");
		}
		TEST_METHOD(TestLoadFont)
		{
			Assert::AreNotEqual(SDL_Init(SDL_INIT_VIDEO), -1);
			Assert::AreNotEqual(TTF_Init(), -1);

			Text text;
			text.loadFont("OpenSans-Bold.ttf");
			Assert::IsNotNull(text.getFont());
	}

		private:
			static Text makeEmptyText()
			{
				return Text();
			}
		
	};

}
