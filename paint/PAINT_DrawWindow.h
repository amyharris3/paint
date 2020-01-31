#pragma once

#include "WIN_Window.h"
#include "PAINT_DrawTool.h"
#include "WIN_ToggleButton.h"
#include "WIN_Coords.h"

struct SDL_Texture;

namespace gfx
{
	class Colour;
}

namespace win
{
	enum class MouseButton;
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
		DrawWindow(SDL_Renderer* renderer, const gfx::Rectangle& rect, const char* name);
		virtual ~DrawWindow();
		DrawWindow(const DrawWindow& that) = delete;
		DrawWindow(DrawWindow&& that) = delete;
		DrawWindow& operator=(const DrawWindow& that) = delete;
		DrawWindow& operator=(DrawWindow&& that) = delete;

		void mouseButtonDown(win::MouseButton button) override;
		void mouseButtonUp(win::MouseButton b) override;
		void setActiveTool(std::shared_ptr<Tool> tool);
		std::shared_ptr<Tool> getActiveTool() const { return activeTool_; };
		void toggleDrawTool(win::ToggleButton* b);
		void setMouseCoords(win::Coords relCoords);
		void setPrevCoords(win::Coords relPrevCoords);
		gfx::Colour getPrimaryColour() const { return primaryColour_; }
		gfx::Colour getSecondaryColour() const { return secondaryColour_; }
		void setPrimaryColour(gfx::Colour colour);
		void setSecondaryColour(gfx::Colour colour);
		void swapColours() override;
		void draw() override;

	private:
		std::shared_ptr<Tool> activeTool_;
		gfx::Colour primaryColour_;
		gfx::Colour secondaryColour_;
		SDL_Renderer* renderer_;
		SDL_Texture* texture_;
		win::Coords mouseCoords_;
		win::Coords prevMouseCoords_;
		std::shared_ptr<Tool> drawTool_;

	};
}