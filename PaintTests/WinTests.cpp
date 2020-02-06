#include "pch.h"
#include "CppUnitTest.h"
#include "TestElement.h"
#include "../win/WIN_FreeLayout.h"
#include "../win/WIN_TableLayout.h"
#include "../gfx/GFX_Rectangle.h"
#include "WIN_ToggleButton.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace gfx;
using namespace win;

namespace PaintTests
{
	TEST_CLASS(TestWinTestElement)
	{
	public:

		TEST_METHOD(TestDefaultConstructionInvariant)
		{
			const TestElement element;
			
			Assert::AreEqual(element.getName(), "dummy");
			
			Assert::AreEqual(element.getRect().x, 0);
			Assert::AreEqual(element.getRect().y, 0);
			Assert::AreEqual(element.getRect().width, 1);
			Assert::AreEqual(element.getRect().height, 1);

			uint8_t rgbaFore[4];
			element.getForegroundColour(rgbaFore);
			Assert::AreEqual(rgbaFore[0], uint8_t(0));
			Assert::AreEqual(rgbaFore[1], uint8_t(1));
			Assert::AreEqual(rgbaFore[2], uint8_t(2));
			Assert::AreEqual(rgbaFore[3], uint8_t(3));

			uint8_t rgbaBack[4];
			element.getBackgroundColour(rgbaBack);
			Assert::AreEqual(rgbaBack[0], uint8_t(250));
			Assert::AreEqual(rgbaBack[1], uint8_t(251));
			Assert::AreEqual(rgbaBack[2], uint8_t(252));
			Assert::AreEqual(rgbaBack[3], uint8_t(253));
		}

		TEST_METHOD(TestSwapColours)
		{
			TestElement element;

			uint8_t rgbaFore[4];
			element.getForegroundColour(rgbaFore);
			Assert::AreEqual(rgbaFore[0], uint8_t(0));
			Assert::AreEqual(rgbaFore[1], uint8_t(1));
			Assert::AreEqual(rgbaFore[2], uint8_t(2));
			Assert::AreEqual(rgbaFore[3], uint8_t(3));

			uint8_t rgbaBack[4];
			element.getBackgroundColour(rgbaBack);
			Assert::AreEqual(rgbaBack[0], uint8_t(250));
			Assert::AreEqual(rgbaBack[1], uint8_t(251));
			Assert::AreEqual(rgbaBack[2], uint8_t(252));
			Assert::AreEqual(rgbaBack[3], uint8_t(253));
			
			element.swapFgBgColours();

			element.getForegroundColour(rgbaFore);
			Assert::AreEqual(rgbaFore[0], uint8_t(250));
			Assert::AreEqual(rgbaFore[1], uint8_t(251));
			Assert::AreEqual(rgbaFore[2], uint8_t(252));
			Assert::AreEqual(rgbaFore[3], uint8_t(253));

			element.getBackgroundColour(rgbaBack);
			Assert::AreEqual(rgbaBack[0], uint8_t(0));
			Assert::AreEqual(rgbaBack[1], uint8_t(1));
			Assert::AreEqual(rgbaBack[2], uint8_t(2));
			Assert::AreEqual(rgbaBack[3], uint8_t(3));
		}
		
	};

	TEST_CLASS(TestWinLayouts)
	{
	public:
		TEST_METHOD(TestDefaultConstructionTableLayout)
		{
			const TableLayout L(5, 10, 3, 6, 1, 2);
			Assert::AreEqual(L.getXMargin(), 5);
			Assert::AreEqual(L.getYMargin(), 10);
			Assert::AreEqual(L.getXSpacing(), 3);
			Assert::AreEqual(L.getYSpacing(), 6);
			Assert::AreEqual(L.getRows(), 1);
			Assert::AreEqual(L.getCols(), 2);
		}

		TEST_METHOD(TestSetRows)
		{
			TableLayout L;
			L.setRows(5);
			Assert::AreEqual(L.getRows(), 5);
		}

		TEST_METHOD(TestSetCols)
		{
			TableLayout L;
			L.setCols(5);
			Assert::AreEqual(L.getCols(), 5);
		}

		TEST_METHOD(TestFreeLayout)
		{
			FreeLayout L;
			const gfx::Rectangle boundary;

			std::vector<std::shared_ptr<UIelement>> elements;
			for (int i = 0; i < 3; i++) {
				auto element = std::make_shared<TestElement>();
				elements.push_back(element);
			}

			L.Apply(elements, boundary);

			for (auto i = 0; i < 1; i++) {
				const auto& box = elements[i]->getRect();
				Assert::AreEqual(box.x, 0);
				Assert::AreEqual(box.y, 0);
				Assert::AreEqual(box.width, 1);
				Assert::AreEqual(box.height, 1);
			}
		}

		TEST_METHOD(TestFreeLayoutEmptyElements)
		{
			TableLayout L(1, 2, 0, 0, 1, 1);
			const gfx::Rectangle boundary(0, 0, 10, 10);

			const std::vector<std::shared_ptr<UIelement>> elements;

			L.Apply(elements, boundary);
		}


		TEST_METHOD(TestTableLayoutApplySingle)
		{
			TableLayout L(1, 2, 0, 0, 1, 1);
			const gfx::Rectangle boundary(0, 0, 10, 10);

			std::vector<std::shared_ptr<UIelement>> elements;
			const auto element = std::make_shared<TestElement>();
			elements.push_back(element);

			L.Apply(elements, boundary);

			const auto& box = element->getRect();
			Assert::AreEqual(box.x, 1);
			Assert::AreEqual(box.y, 2);
			Assert::AreEqual(box.width, 8);
			Assert::AreEqual(box.height, 6);
			Assert::IsTrue(boundary.containsPoint(box.x, box.y));
		}

		TEST_METHOD(TestTableLayoutApply1xN)
		{
			TableLayout L(1, 2, 1, 1, 1, 5);
			const gfx::Rectangle boundary(0, 0, 26, 10);

			std::vector<std::shared_ptr<UIelement>> elements;
			for (int i = 0; i < 5; i++) {
				auto element = std::make_shared<TestElement>();
				elements.push_back(element);
			}

			L.Apply(elements, boundary);

			int xCount = 0;
			for (const auto& element : elements) {
				const auto& box = element->getRect();
				Assert::AreEqual(box.x, 1 + (5 * xCount));
				Assert::AreEqual(box.y, 2);
				Assert::AreEqual(box.width, 4);
				Assert::AreEqual(box.height, 6);
				Assert::IsTrue(boundary.containsPoint(box.x, box.y));

				xCount++;
			}
		}

		TEST_METHOD(TestTableLayoutApplyNx1)
		{
			TableLayout L(2, 1, 1, 1, 5, 1);
			const gfx::Rectangle boundary(0, 0, 10, 26);

			std::vector<std::shared_ptr<UIelement>> elements;
			for (int i = 0; i < 5; i++) {
				auto element = std::make_shared<TestElement>();
				elements.push_back(element);
			}

			L.Apply(elements, boundary);

			auto yCount = 0;
			for (const auto& element : elements) {
				const auto& box = element->getRect();
				Assert::AreEqual(box.x, 2);
				Assert::AreEqual(box.y, 1 + (5 * yCount));
				Assert::AreEqual(box.width, 6);
				Assert::AreEqual(box.height, 4);
				Assert::IsTrue(boundary.containsPoint(box.x, box.y));

				yCount++;
			}
		}

		TEST_METHOD(TestTableLayoutApply)
		{
			TableLayout L(10, 10, 5, 5, 3, 2);
			const gfx::Rectangle boundary(0, 0, 65, 90);

			std::vector<std::shared_ptr<UIelement>> elements;
			for (int i = 0; i < 6; i++) {
				auto element = std::make_shared<TestElement>();
				elements.push_back(element);
			}

			L.Apply(elements, boundary);

			auto xCount = 0;
			auto yCount = 0;

			//test to ensure that all elements have correct position and dimensions, 
			//and that they are still within boundaries, after layout is applied
			for (const auto& element : elements) {
				const auto& box = element->getRect();
				Assert::AreEqual(box.x, 10 + (25 * xCount));
				Assert::AreEqual(box.y, 10 + (25 * yCount));
				Assert::AreEqual(box.width, 20);
				Assert::AreEqual(box.height, 20);
				Assert::IsTrue(boundary.containsPoint(box.x, box.y));

				xCount++;
				if (xCount == 2) {
					xCount = 0;
					yCount++;
				}

			}
		}

	};
	
}
