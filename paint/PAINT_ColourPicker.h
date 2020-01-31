#pragma once
#include "WIN_Container.h"
#include "WIN_ColourDisplay.h"
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
		ColourPicker(gfx::Rectangle rect, SDL_Renderer* renderer, std::shared_ptr<DrawWindow> const & drawWindow);
		~ColourPicker() = default;
		ColourPicker(const ColourPicker & that) = default;
		ColourPicker(ColourPicker && that) = default;
		ColourPicker& operator=(const ColourPicker & that) = default;
		ColourPicker& operator=(ColourPicker && that) = default;

		void initialiseColourDisplays();
		void initialiseColourValueBoxes();
		void initialiseColourSliders();
		
		std::shared_ptr<win::ColourValueTextbox> getRedValueBox() const { return redValueBox_;  }
		std::shared_ptr<win::ColourValueTextbox> getGreenValueBox() const { return greenValueBox_;  }
		std::shared_ptr<win::ColourValueTextbox> getBlueValueBox() const { return blueValueBox_;  }
		std::shared_ptr<win::ColourValueTextbox> getAlphaValueBox() const { return alphaValueBox_;  }
		
		void setDrawColourFromActive() const;
		void setPrimarySecondaryFromActiveDraw() const;
		void updateColourDisplaysFromDrawWindow() const;
		void updateColourDisplays() const;
		void updateColourValueBoxes() const;
		void updateColourSliders() const;
		void swapActiveColour() const;
		void swapDisplaysSwitch() { swappedDisplays_= !swappedDisplays_; }

		void update() override;
		void updateAndRerender() override;
		void draw() override;
		bool mouseButtonDown(win::MouseButton const button) override;
		bool mouseButtonUp(win::MouseButton const button) override;
		
	private:

		std::shared_ptr<DrawWindow> drawWindowPtr_;
		SDL_Renderer* renderer_;
		
		std::shared_ptr<Container> displayBox_;
		std::shared_ptr<win::ColourDisplay> primaryColourDisplay_;
		std::shared_ptr<win::ColourDisplay> secondaryColourDisplay_;
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
		

	};
}
