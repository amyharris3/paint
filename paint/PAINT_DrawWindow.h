#pragma once

#include "WIN_Window.h"
#include "PAINT_DrawTool.h"
#include "WIN_ToggleButton.h"
#include "WIN_Coords.h"

struct SDL_Texture;

namespace gfx
{
	class Colour;
	//class Line;
}

namespace win
{
	enum class MouseButton;
	struct Coords;
}

namespace paint 
{
	class Tool;
	class Brush;

	class DrawWindow final :
		public win::Window
	{

	public:
		DrawWindow() = delete;
		DrawWindow(gfx::Renderer* renderer, const gfx::Rectangle& rect, const char* name);

		virtual ~DrawWindow();
		DrawWindow(const DrawWindow& that) = delete;
		DrawWindow(DrawWindow&& that) = delete;
		DrawWindow& operator=(const DrawWindow& that) = delete;
		DrawWindow& operator=(DrawWindow&& that) = delete;

		bool mouseButtonDown(win::MouseButton button) override;
		bool mouseButtonUp(win::MouseButton b) override;
		void setActiveTool(std::shared_ptr<Tool> tool);
		std::shared_ptr<Tool> getActiveTool() const { return activeTool_; };
		void toggleDrawTool(win::ToggleButton* b);
		void setMouseCoords(win::Coords relCoords);
		void setPrevCoords(win::Coords relPrevCoords);
		gfx::Colour getPrimaryColour() const { return primaryColour_; }
		gfx::Colour getSecondaryColour() const { return secondaryColour_; }
		void setPrimaryColour(gfx::Colour colour);
		void setSecondaryColour(gfx::Colour colour);
		bool isPrimaryActive() const { return primaryActive_; }
		void setIfPrimaryColourActive(const bool b) { primaryActive_ = b; }
		//void swapPrimarySecondaryColours();

		void updateDrawToolRGBA();
		uint8_t* getPrimaryRGBA() { return primaryRGBA_; }
		uint8_t* getSecondaryRGBA() { return secondaryRGBA_; }
	
		//void setColor(SDL_Surface* surface);
		void draw() override;
		void updateAndRerender() override;
		void clearScreen() const;

	private:
		gfx::Renderer* renderer_;
		
		std::shared_ptr<Tool> activeTool_;
		std::shared_ptr<Tool> drawTool_;
		gfx::Colour primaryColour_;
		gfx::Colour secondaryColour_;
		std::vector<win::Coords> clickedPixels_;
		bool drawToggle_;
		win::Coords mouseCoords_;
		win::Coords prevMouseCoords_;
		std::vector<gfx::Line> lines_;

		//whenever the active colour is changed this should be updated
		bool primaryActive_;
		uint8_t primaryRGBA_[4];
		uint8_t secondaryRGBA_[4];
	};
}