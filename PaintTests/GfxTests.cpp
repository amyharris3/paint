#include "pch.h"
#include "CppUnitTest.h"
#include "../gfx/GFX_Rectangle.h"
#include "../gfx/GFX_colour.h"

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
			return Rectangle();
		}
	};

	TEST_CLASS(TestGfxColour)
	{
	public:

		TEST_METHOD(TestDefaultConstructor)
		{
			Colour c(10, 20, 30, 40);
			uint8_t rgba[4];
			c.getComponents(rgba);
			Assert::AreEqual(rgba[0], (uint8_t)10);
			Assert::AreEqual(rgba[1], (uint8_t)20);
			Assert::AreEqual(rgba[2], (uint8_t)30);
			Assert::AreEqual(rgba[3], (uint8_t)40);
		}
		TEST_METHOD(TestCopyConstruction)
		{
			const Colour c1(10, 20, 30, 40);
			Colour c2(c1);
			uint8_t rgba[4];
			c2.getComponents(rgba);
			Assert::AreEqual(rgba[0], (uint8_t)10);
			Assert::AreEqual(rgba[1], (uint8_t)20);
			Assert::AreEqual(rgba[2], (uint8_t)30);
			Assert::AreEqual(rgba[3], (uint8_t)40);
		}

		TEST_METHOD(TestAsssignmentOperator)
		{
			const  Colour c1(10, 20, 30, 40);
			Colour c2 = c1;
			uint8_t rgba[4];
			c2.getComponents(rgba);
			Assert::AreEqual(rgba[0], (uint8_t)10);
			Assert::AreEqual(rgba[1], (uint8_t)20);
			Assert::AreEqual(rgba[2], (uint8_t)30);
			Assert::AreEqual(rgba[3], (uint8_t)40);
		}

		TEST_METHOD(TestMoveConstructor)
		{
			Colour c(makeWhite());
			uint8_t rgba[4];
			c.getComponents(rgba);
			Assert::AreEqual(rgba[0], (uint8_t)255);
			Assert::AreEqual(rgba[1], (uint8_t)255);
			Assert::AreEqual(rgba[2], (uint8_t)255);
			Assert::AreEqual(rgba[3], (uint8_t)255);
		}

		TEST_METHOD(TestMoveAssignmentOperator)
		{
			Colour c = makeWhite();
			uint8_t rgba[4];
			c.getComponents(rgba);
			Assert::AreEqual(rgba[0], (uint8_t)255);
			Assert::AreEqual(rgba[1], (uint8_t)255);
			Assert::AreEqual(rgba[2], (uint8_t)255);
			Assert::AreEqual(rgba[3], (uint8_t)255);
		}

		TEST_METHOD(TestGetComponents)
		{
			Colour c(10, 20, 30, 40);
			uint8_t rgba[4];
			c.getComponents(rgba);
			Assert::AreEqual(rgba[0], (uint8_t)10);
			Assert::AreEqual(rgba[1], (uint8_t)20);
			Assert::AreEqual(rgba[2], (uint8_t)30);
			Assert::AreEqual(rgba[3], (uint8_t)40);
		}

	private:
		static Colour makeWhite()
		{
			return Colour(255, 255, 255, 255);
		}
	};
}
