#pragma once
#include "WIN_Container.h"
#include "PAINT_ColourDisplay.h"
#include "WIN_Button.h"
#include "WIN_ColourValueTextbox.h"
#include "WIN_ColourSlider.h"

namespace paint
{
	class DrawWindow;
	
	class ColourPicker final : public win::Container
	{
	public:
		
		ColourPicker() = delete;
		ColourPicker(gfx::Rectangle rect, gfx::Renderer* renderer, std::shared_ptr<DrawWindow> drawWindow);
		~ColourPicker() = default;
		ColourPicker(const ColourPicker & that) = default;
		ColourPicker(ColourPicker && that) = default;
		ColourPicker& operator=(const ColourPicker & that) = default;
		ColourPicker& operator=(ColourPicker && that) = default;

		std::shared_ptr<win::ColourValueTextbox> getRedValueBox() const { return redValueBox_;  }
		std::shared_ptr<win::ColourValueTextbox> getGreenValueBox() const { return greenValueBox_;  }
		std::shared_ptr<win::ColourValueTextbox> getBlueValueBox() const { return blueValueBox_;  }
		std::shared_ptr<win::ColourValueTextbox> getAlphaValueBox() const { return alphaValueBox_;  }
		
		void setActiveColourInDrawWindow() const;

		void PrimaryActiveSwitchInBoxSlider() const;
		void swapActiveColour() const;
		void swappedDisplaysSwitch() { swappedDisplays_ = !swappedDisplays_; }

		void updateColourDisplaysFromDrawWindow() const;

		void update() override;
		void updateAndRerender() override;
		void draw() override;
		
	private:

		std::shared_ptr<DrawWindow> drawWindowPtr_;
		gfx::Renderer* renderer_;
		
		std::shared_ptr<Container> displayBox_;
		std::shared_ptr<ColourDisplay> leftColourDisplay_;
		std::shared_ptr<ColourDisplay> rightColourDisplay_;
		std::shared_ptr<win::Button> swapButton_;
		bool swappedDisplays_;

		std::shared_ptr<Container> colourValuesBox_;
		std::shared_ptr<win::ColourValueTextbox> redValueBox_;
		std::shared_ptr<win::ColourValueTextbox> greenValueBox_;
		std::shared_ptr<win::ColourValueTextbox> blueValueBox_;
		std::shared_ptr<win::ColourValueTextbox> alphaValueBox_;

		std::shared_ptr<Container> colourSliders_;
		std::shared_ptr<win::ColourSlider> redValueSlider_;
		std::shared_ptr<win::ColourSlider> greenValueSlider_;
		std::shared_ptr<win::ColourSlider> blueValueSlider_;
		std::shared_ptr<win::ColourSlider> alphaValueSlider_;

		inline void initialiseColourDisplays();
		inline void initialiseColourValueBoxes();
		inline void initialiseColourSliders();

		void updateColourDisplays() const;
		void updateColourValueBoxes() const;
		void updateColourSliders() const;
	};
}
