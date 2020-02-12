#include "pch.h"
#include "CppUnitTest.h"
#include "TestElement.h"
#include "../win/WIN_FreeLayout.h"
#include "../win/WIN_TableLayout.h"
#include "../gfx/GFX_Rectangle.h"
#include <memory>
#include "WIN_Container.h"
#include "WIN_Window.h"
#include "WIN_EditTextbox.h"
#include "WIN_ColourValueTextbox.h"
#include "WIN_Slider.h"
#include "WIN_Utils.h"
#include "WIN_SDLRenderer.h"
#include "GFX_Utils.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace gfx;
using namespace win;

namespace PaintTests
{
	TEST_CLASS(TestWinTestElement)
	{
	public:

		//UIelement is virtual, so we create a TestElement class to test instead
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

		TEST_METHOD(TestSetRect)
		{
			TestElement element;
			element.setRect({ 20,30,40,50 });
			Assert::AreEqual(element.getRect().x, 20);
			Assert::AreEqual(element.getRect().y, 30);
			Assert::AreEqual(element.getRect().width, 40);
			Assert::AreEqual(element.getRect().height, 50);
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

		TEST_METHOD(TestChangeColours)
		{
			TestElement element;
			uint8_t rgbaFore[4];
			element.getForegroundColour(rgbaFore);
			Assert::AreEqual(rgbaFore[0], uint8_t(0));
			Assert::AreEqual(rgbaFore[1], uint8_t(1));
			Assert::AreEqual(rgbaFore[2], uint8_t(2));
			Assert::AreEqual(rgbaFore[3], uint8_t(3));

			element.setForegroundColour({ 50, 150, 200, 250 });
			element.getForegroundColour(rgbaFore);
			Assert::AreEqual(rgbaFore[0], uint8_t(50));
			Assert::AreEqual(rgbaFore[1], uint8_t(150));
			Assert::AreEqual(rgbaFore[2], uint8_t(200));
			Assert::AreEqual(rgbaFore[3], uint8_t(250));

			uint8_t rgbaBack[4];
			element.getBackgroundColour(rgbaBack);
			Assert::AreEqual(rgbaBack[0], uint8_t(250));
			Assert::AreEqual(rgbaBack[1], uint8_t(251));
			Assert::AreEqual(rgbaBack[2], uint8_t(252));
			Assert::AreEqual(rgbaBack[3], uint8_t(253));

			element.setBackgroundColour({ 55, 155, 205, 255 });
			element.getBackgroundColour(rgbaBack);
			Assert::AreEqual(rgbaBack[0], uint8_t(55));
			Assert::AreEqual(rgbaBack[1], uint8_t(155));
			Assert::AreEqual(rgbaBack[2], uint8_t(205));
			Assert::AreEqual(rgbaBack[3], uint8_t(255));
		}

		TEST_METHOD(TestParent)
		{
			TestElement parentElement;
			TestElement childElement;

			Assert::IsNull(childElement.getParent());
			childElement.setParent(&parentElement);
			Assert::IsNotNull(childElement.getParent());
			Assert::IsTrue(&parentElement == childElement.getParent());
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

	TEST_CLASS(TestWinContainer)
	{
	public:
		TEST_METHOD(TestDefaultConstructor)
		{
			const Container c;

			Assert::IsNotNull(c.getLayout().get());
			Assert::AreEqual(c.getRect().x, 0);
			Assert::AreEqual(c.getRect().y, 0);
			Assert::AreEqual(c.getRect().width, 1);
			Assert::AreEqual(c.getRect().height, 1);
			Assert::AreEqual(c.getName(), "container");
			Assert::IsFalse(c.getDirtyFlag());
		}

		TEST_METHOD(TestCopyConstruction)
		{
			const Container a;
			const Container b(a);

			Assert::AreEqual(a.getName(), b.getName());
			Assert::IsTrue(a.getLayout() == b.getLayout());
			
			Assert::AreEqual(a.getRect().x, b.getRect().x);
			Assert::AreEqual(a.getRect().y, b.getRect().y);
			Assert::AreEqual(a.getRect().width, b.getRect().width);
			Assert::AreEqual(a.getRect().height, b.getRect().height);

			uint8_t rgba_a[4];
			uint8_t rgba_b[4];
			
			a.getForegroundColour().getComponents(rgba_a);
			b.getForegroundColour().getComponents(rgba_b);
			Assert::AreEqual(rgba_a[0], rgba_a[0]);
			Assert::AreEqual(rgba_a[1], rgba_a[1]);
			Assert::AreEqual(rgba_a[2], rgba_a[2]);
			Assert::AreEqual(rgba_a[3], rgba_a[3]);

			a.getBackgroundColour().getComponents(rgba_a);
			b.getBackgroundColour().getComponents(rgba_b);
			Assert::AreEqual(rgba_a[0], rgba_a[0]);
			Assert::AreEqual(rgba_a[1], rgba_a[1]);
			Assert::AreEqual(rgba_a[2], rgba_a[2]);
			Assert::AreEqual(rgba_a[3], rgba_a[3]);
		}

		TEST_METHOD(TestAssignmentOperator)
		{
			const Container a;
			const Container b = a;

			Assert::AreEqual(a.getName(), b.getName());
			Assert::IsTrue(a.getLayout() == b.getLayout());

			Assert::AreEqual(a.getRect().x, b.getRect().x);
			Assert::AreEqual(a.getRect().y, b.getRect().y);
			Assert::AreEqual(a.getRect().width, b.getRect().width);
			Assert::AreEqual(a.getRect().height, b.getRect().height);

			uint8_t rgba_a[4];
			uint8_t rgba_b[4];

			a.getForegroundColour().getComponents(rgba_a);
			b.getForegroundColour().getComponents(rgba_b);
			Assert::AreEqual(rgba_a[0], rgba_a[0]);
			Assert::AreEqual(rgba_a[1], rgba_a[1]);
			Assert::AreEqual(rgba_a[2], rgba_a[2]);
			Assert::AreEqual(rgba_a[3], rgba_a[3]);

			a.getBackgroundColour().getComponents(rgba_a);
			b.getBackgroundColour().getComponents(rgba_b);
			Assert::AreEqual(rgba_a[0], rgba_a[0]);
			Assert::AreEqual(rgba_a[1], rgba_a[1]);
			Assert::AreEqual(rgba_a[2], rgba_a[2]);
			Assert::AreEqual(rgba_a[3], rgba_a[3]);
		}

		TEST_METHOD(TestMoveConstructor)
		{
			const Container c(makeEmptyContainer());
			Assert::AreEqual(c.getRect().x, 0);
			Assert::AreEqual(c.getRect().y, 0);
			Assert::AreEqual(c.getRect().width, 1);
			Assert::AreEqual(c.getRect().height, 1);
			Assert::AreEqual(c.getName(), "container");
			Assert::IsNotNull(c.getLayout().get());
		}

		TEST_METHOD(TestMoveAssignmentOperator)
		{
			const Container c = makeEmptyContainer();
			Assert::AreEqual(c.getRect().x, 0);
			Assert::AreEqual(c.getRect().y, 0);
			Assert::AreEqual(c.getRect().width, 1);
			Assert::AreEqual(c.getRect().height, 1);
			Assert::AreEqual(c.getName(), "container");
			Assert::IsNotNull(c.getLayout().get());
		}
		TEST_METHOD(TestChildren)
		{
			Container c;
			
			for (int i = 0; i < 3; i++) {
				auto element = std::make_shared<TestElement>();
				c.addChild(element);
			}

			for (const auto& child : c.getChildren()){
				Assert::IsNotNull(child.get());
				Assert::IsTrue(child->getParent() == &c);
			}
		}
		
		TEST_METHOD(TestApplyFreeLayout)
		{
			Container c (std::make_shared<FreeLayout>(), gfx::Rectangle(), "test");

			for (int i = 0; i < 3; i++) {
				auto element = std::make_shared<TestElement>();
				c.addChild(element);
			}

			c.applyLayout();
			
			for (const auto& child : c.getChildren()) {
				Assert::AreEqual(child->getRect().x, 0);
				Assert::AreEqual(child->getRect().y, 0);
				Assert::AreEqual(child->getRect().width, 1);
				Assert::AreEqual(child->getRect().height, 1);
				Assert::IsTrue(c.getRect().containsPoint(child->getRect().x, child->getRect().y));
			}
		}

		TEST_METHOD(TestApplyTableLayout)
		{
			Container c(std::make_shared<TableLayout>(10, 10, 5, 5, 3, 2), gfx::Rectangle(0, 0, 65, 90), "test");

			for (int i = 0; i < 6; i++) {
				auto element = std::make_shared<TestElement>();
				c.addChild(element);
			}

			c.applyLayout();

			int xcount = 0;
			int ycount = 0;
			for (const auto& child : c.getChildren()) {
				Assert::AreEqual(child->getRect().x, 10 + (25 * xcount));
				Assert::AreEqual(child->getRect().y, 10 + (25 * ycount));
				Assert::AreEqual(child->getRect().width, 20);
				Assert::AreEqual(child->getRect().height, 20);
				Assert::IsTrue(c.getRect().containsPoint(child->getRect().x, child->getRect().y));

				xcount++;
				if (xcount == 2) {
					xcount = 0;
					ycount++;
				}
			}
		}

	private:
		static Container makeEmptyContainer()
		{
			return {};
		}
		
	};

	TEST_CLASS(TestWinWindow)
	{
	public:
		TEST_METHOD(TestConstructor)
		{
			const Window W(gfx::Rectangle(), "test");

			Assert::AreEqual(W.getName(), "test");

			Assert::AreEqual(W.getRect().x, 0);
			Assert::AreEqual(W.getRect().y, 0);
			Assert::AreEqual(W.getRect().width, 1);
			Assert::AreEqual(W.getRect().height, 1);
			
		}

		//A Window is effectively just a container with a renderer and draw function attached,
		//hence testing copy/move/ect operators is lower priority as we have already tested for Container		
	};

	TEST_CLASS(TestWinEditTextbox)
	{
	public:
		TEST_METHOD(TestConstructor)
		{
			const EditTextbox box(gfx::Rectangle(), "textbox", 20, 5, 10);
			
			Assert::AreEqual(box.getName(), "textbox");
			Assert::AreEqual(box.getText()->getString().c_str(), "");
			Assert::AreEqual(box.getText()->getTextSize(), 20);
			Assert::AreEqual(box.getXOffset(), 5);
			Assert::AreEqual(box.getYOffset(), 10);

			Assert::AreEqual(box.getRect().x, 0);
			Assert::AreEqual(box.getRect().y, 0);
			Assert::AreEqual(box.getRect().width, 1);
			Assert::AreEqual(box.getRect().height, 1);

			uint8_t rgba[4];
			box.getBackgroundColour().getComponents(rgba);
			Assert::AreEqual(rgba[0], uint8_t(255));
			Assert::AreEqual(rgba[1], uint8_t(255));
			Assert::AreEqual(rgba[2], uint8_t(255));
			Assert::AreEqual(rgba[3], uint8_t(255));
		}

		TEST_METHOD(TestEditText)
		{
			EditTextbox box(gfx::Rectangle(), "textbox", 20, 5, 10);

			Assert::AreEqual(box.getText()->getString().c_str(), "");
			box.editText("newText");
			Assert::AreEqual(box.getText()->getString().c_str(), "newText");
		}

	};
	
	TEST_CLASS(TestWinColourValueTextbox)
	{
	public:
		TEST_METHOD(TestConstructor)
		{
			uint8_t colA = 0;
			uint8_t colB = 5;
			ColourValueTextbox box(gfx::Rectangle(), "textbox", 20, 5, 10, &colA, &colB, true);

			Assert::AreEqual(box.getName(), "textbox");
			Assert::AreEqual(box.getText()->getTextSize(), 20);
			Assert::AreEqual(box.getXOffset(), 5);
			Assert::AreEqual(box.getYOffset(), 10);

			Assert::AreEqual(box.getRect().x, 0);
			Assert::AreEqual(box.getRect().y, 0);
			Assert::AreEqual(box.getRect().width, 1);
			Assert::AreEqual(box.getRect().height, 1);

			Assert::AreEqual(box.getText()->getString().c_str(), "0");
			box.primaryActiveSwitch();
			Assert::AreEqual(box.getText()->getString().c_str(), "5");

			uint8_t rgba[4];
			box.getBackgroundColour().getComponents(rgba);
			Assert::AreEqual(rgba[0], uint8_t(255));
			Assert::AreEqual(rgba[1], uint8_t(255));
			Assert::AreEqual(rgba[2], uint8_t(255));
			Assert::AreEqual(rgba[3], uint8_t(255));

			Assert::IsTrue(box.getLinkedPrimary() == &colA);
			Assert::IsTrue(box.getLinkedSecondary() == &colB);
		}

		TEST_METHOD(TestChangeTextInternally)
		{
			uint8_t colA = 0;
			uint8_t colB = 5;
			ColourValueTextbox box(gfx::Rectangle(), "textbox", 20, 5, 10, &colA, &colB, true);

			Assert::AreEqual(colA, uint8_t(0));
			Assert::AreEqual(colB, uint8_t(5));

			//mocking text entry
			box.editText("100");
			box.primaryActiveSwitch();
			box.editText("200");

			Assert::AreEqual(*(box.getLinkedPrimary()), uint8_t(100));
			Assert::AreEqual(colA, uint8_t(100));
			Assert::AreEqual(*(box.getLinkedSecondary()), uint8_t(200));
			Assert::AreEqual(colB, uint8_t(200));
		}

		TEST_METHOD(TestChangeTextExternally)
		{
			uint8_t colA = 0;
			uint8_t colB = 5;
			const ColourValueTextbox box(gfx::Rectangle(), "textbox",20, 5, 10, &colA, &colB, true);

			Assert::AreEqual(colA, uint8_t(0));
			Assert::AreEqual(colB, uint8_t(5));

			colA = 155;
			colB = 220;

			Assert::AreEqual(*(box.getLinkedPrimary()), uint8_t(155));
			Assert::AreEqual(colA, uint8_t(155));
			Assert::AreEqual(*(box.getLinkedSecondary()), uint8_t(220));
			Assert::AreEqual(colB, uint8_t(220));
		}

	};

	TEST_CLASS(TestWinSlider)
	{
	public:
		TEST_METHOD(TestConstructor)
		{
			const Slider slider(gfx::Rectangle(), "slider", gfx::Colour(210, 220, 230, 240), gfx::Colour(1, 2, 3, 4), 0, 0, 10);

			// general slider dimensions + properties
			Assert::AreEqual(slider.getName(), "slider");

			Assert::AreEqual(slider.getRect().x, 0);
			Assert::AreEqual(slider.getRect().y, 0);
			Assert::AreEqual(slider.getRect().width, 1);
			Assert::AreEqual(slider.getRect().height, 1);

			uint8_t rgba[4];
			slider.getForegroundColour().getComponents(rgba);
			Assert::AreEqual(rgba[0], uint8_t(210));
			Assert::AreEqual(rgba[1], uint8_t(220));
			Assert::AreEqual(rgba[2], uint8_t(230));
			Assert::AreEqual(rgba[3], uint8_t(240));

			slider.getBackgroundColour().getComponents(rgba);
			Assert::AreEqual(rgba[0], uint8_t(1));
			Assert::AreEqual(rgba[1], uint8_t(2));
			Assert::AreEqual(rgba[2], uint8_t(3));
			Assert::AreEqual(rgba[3], uint8_t(4));

			// specific line properties
			Assert::AreEqual(slider.getLineRect().x, 0);
			Assert::AreEqual(slider.getLineRect().y, 0);
			Assert::AreEqual(slider.getLineRect().width, 1);
			Assert::AreEqual(slider.getLineRect().height, 1);

			// specific marker properties
			Assert::AreEqual(slider.getMarkerRect().x, 0);
			Assert::AreEqual(slider.getMarkerRect().y, 0);
			Assert::AreEqual(slider.getMarkerRect().width, 1);
			Assert::AreEqual(slider.getMarkerRect().height, 1);
			Assert::AreEqual(slider.getMarkerPos(), slider.getMarkerRect().x);
		}

		TEST_METHOD(TestConstructorNondefault)
		{
			const Slider slider(gfx::Rectangle(0,0,100,20), "slider", gfx::Colour(210, 220, 230, 240), gfx::Colour(1, 2, 3, 4), 50, 0, 200);

			Assert::AreEqual(slider.getLineRect().x, 2);
			Assert::AreEqual(slider.getLineRect().y,8);
			Assert::AreEqual(slider.getLineRect().width, 95);
			Assert::AreEqual(slider.getLineRect().height, 3);

			Assert::AreEqual(slider.getMarkerValue(), 50);		
			Assert::AreEqual(slider.getMarkerRect().x, 26);
			Assert::AreEqual(slider.getMarkerRect().y, 0);
			Assert::AreEqual(slider.getMarkerRect().width, 5);
			Assert::AreEqual(slider.getMarkerRect().height, 20);
		}
		
		TEST_METHOD(TestChangePosition)
		{
			Slider slider(gfx::Rectangle(0, 0, 100, 20), "slider", gfx::Colour(210, 220, 230, 240), gfx::Colour(1, 2, 3, 4), 50, 0, 200);

			slider.setMarkerPos(20);
			Assert::AreEqual(slider.getMarkerPos(), 20);
			Assert::AreEqual(slider.getMarkerValue(), 38);

			slider.setMarkerPos(55);
			Assert::AreEqual(slider.getMarkerPos(), 55);
			Assert::AreEqual(slider.getMarkerValue(), 112);
			
			slider.setMarkerPos(250);
			Assert::AreEqual(slider.getMarkerPos(), 100 - 3);
			Assert::AreEqual(slider.getMarkerValue(), 200);

			slider.setMarkerPos(-100);
			Assert::AreEqual(slider.getMarkerPos(), 2);
			Assert::AreEqual(slider.getMarkerValue(), 0);
		}

		TEST_METHOD(TestChangeValue)
		{
			Slider slider(gfx::Rectangle(0, 0, 100, 20), "slider", gfx::Colour(210, 220, 230, 240), gfx::Colour(1, 2, 3, 4), 50, 0, 200);

			slider.setMarkerValue(20);
			Assert::AreEqual(slider.getMarkerValue(), 20);
			Assert::AreEqual(slider.getMarkerPos(), 12);

			slider.setMarkerValue(123);
			Assert::AreEqual(slider.getMarkerValue(), 123);
			Assert::AreEqual(slider.getMarkerPos(), 60);

			slider.setMarkerValue(500);
			Assert::AreEqual(slider.getMarkerValue(), 200);
			Assert::AreEqual(slider.getMarkerPos(), 100 - 3);
			
			slider.setMarkerValue(-100);
			Assert::AreEqual(slider.getMarkerValue(), 0);
			Assert::AreEqual(slider.getMarkerPos(), 2);

		}

	};
	

	TEST_CLASS(TestWinColourValueSlider)
	{
	public:
		TEST_METHOD(TestConstructor)
		{
			uint8_t colA = 0;
			uint8_t colB = 5;
			ColourValueTextbox box(gfx::Rectangle(), "textbox", 20, 5, 10, &colA, &colB, true);

			Assert::AreEqual(box.getName(), "textbox");
			Assert::AreEqual(box.getText()->getTextSize(), 20);
			Assert::AreEqual(box.getXOffset(), 5);
			Assert::AreEqual(box.getYOffset(), 10);

			Assert::AreEqual(box.getRect().x, 0);
			Assert::AreEqual(box.getRect().y, 0);
			Assert::AreEqual(box.getRect().width, 1);
			Assert::AreEqual(box.getRect().height, 1);

			Assert::AreEqual(box.getText()->getString().c_str(), "0");
			box.primaryActiveSwitch();
			Assert::AreEqual(box.getText()->getString().c_str(), "5");

			uint8_t rgba[4];
			box.getBackgroundColour().getComponents(rgba);
			Assert::AreEqual(rgba[0], uint8_t(255));
			Assert::AreEqual(rgba[1], uint8_t(255));
			Assert::AreEqual(rgba[2], uint8_t(255));
			Assert::AreEqual(rgba[3], uint8_t(255));

			Assert::IsTrue(box.getLinkedPrimary() == &colA);
			Assert::IsTrue(box.getLinkedSecondary() == &colB);
		}

		TEST_METHOD(TestChangeValueInternally)
		{
			uint8_t colA = 0;
			uint8_t ColB = 5;
			ColourValueTextbox box(gfx::Rectangle(), "textbox", 20, 5, 10, &colA, &ColB, true);

			Assert::AreEqual(colA, uint8_t(0));
			Assert::AreEqual(ColB, uint8_t(5));

			//mocking text entry
			box.editText("100");
			box.primaryActiveSwitch();
			box.editText("200");

			Assert::AreEqual(*(box.getLinkedPrimary()), uint8_t(100));
			Assert::AreEqual(colA, uint8_t(100));
			Assert::AreEqual(*(box.getLinkedSecondary()), uint8_t(200));
			Assert::AreEqual(ColB, uint8_t(200));
		}

		TEST_METHOD(TestChangeValueExternally)
		{
			uint8_t colA = 0;
			uint8_t colB = 5;
			const ColourValueTextbox box(gfx::Rectangle(), "textbox", 20, 5, 10, &colA, &colB, true);

			Assert::AreEqual(colA, uint8_t(0));
			Assert::AreEqual(colB, uint8_t(5));

			colA = 155;
			colB = 220;

			Assert::AreEqual(*(box.getLinkedPrimary()), uint8_t(155));
			Assert::AreEqual(colA, uint8_t(155));
			Assert::AreEqual(*(box.getLinkedSecondary()), uint8_t(220));
			Assert::AreEqual(colB, uint8_t(220));
		}

	};

	TEST_CLASS(TestWinUtils)
	{
		TEST_METHOD(TestFilterNumerical)
		{
			Assert::IsFalse(win::utils::filterNumerical('a'));
			Assert::IsFalse(win::utils::filterNumerical('A'));
			Assert::IsTrue(win::utils::filterNumerical('1'));
			Assert::IsTrue(win::utils::filterNumerical('9'));
			Assert::IsTrue(win::utils::filterNumerical('0'));
			Assert::IsFalse (win::utils::filterNumerical('/'));
			Assert::IsFalse(win::utils::filterNumerical('.'));
			Assert::IsFalse(win::utils::filterNumerical('['));
			Assert::IsFalse(win::utils::filterNumerical('+'));
			Assert::IsFalse(win::utils::filterNumerical('!'));
		}

		TEST_METHOD(TestOutcode)
		{
			const gfx::Rectangle rect(10, 10, 10, 10);

			Assert::AreEqual(gfx::utils::findOutcode(rect, 15, 15), 0);
			Assert::AreEqual(gfx::utils::findOutcode(rect, 5, 15), 1);
			Assert::AreEqual(gfx::utils::findOutcode(rect, 25, 15), 2);
			Assert::AreEqual(gfx::utils::findOutcode(rect, 15, 5), 8);
			Assert::AreEqual(gfx::utils::findOutcode(rect, 15, 25), 4);
			Assert::AreEqual(gfx::utils::findOutcode(rect, 5, 5), 9);
			Assert::AreEqual(gfx::utils::findOutcode(rect, 5, 25), 5);
			Assert::AreEqual(gfx::utils::findOutcode(rect, 25, 5), 10);
			Assert::AreEqual(gfx::utils::findOutcode(rect, 25, 25), 6);
			
		}
		
	};
	
}
