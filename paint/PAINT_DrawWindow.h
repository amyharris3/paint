#pragma once

#include "WIN_Window.h"
#include "PAINT_DrawTool.h"
#include "WIN_ToggleButton.h"
#include "GFX_Coords.h"

struct SDL_Texture;

namespace gfx
{
	struct Coords;
	class Colour;
}

namespace win
{
	enum class MouseButton;
}

namespace paint 
{
	class DrawTool;
	class Brush;
	class ShapeTool;
	class Tool;

	class DrawWindow final :
		public win::Window
	{

	public:
		DrawWindow() = delete;
		DrawWindow(win::SDLRenderer* renderer, const gfx::Rectangle& rect, const char* name);

		virtual ~DrawWindow() = default;
		DrawWindow(const DrawWindow& that) = delete;
		DrawWindow(DrawWindow&& that) = delete;
		DrawWindow& operator=(const DrawWindow& that) = delete;
		DrawWindow& operator=(DrawWindow&& that) = delete;

		bool mouseEnter(win::MouseButton button,  bool clicked = false) override;
		bool mouseExit(win::MouseButton button, bool clicked = false) override;
		bool mouseButtonDown(win::MouseButton button, bool clicked = false) override;
		bool mouseButtonUp(win::MouseButton button, bool clicked = false, win::SDLRenderer* renderer = nullptr) override;
		
		void setActiveTool(std::shared_ptr<Tool> tool);
		std::shared_ptr<Tool> getActiveTool() const { return activeTool_; }
		void toggleDrawTool(win::ToggleButton* b);
		void toggleShapeTool(win::ToggleButton* b);
		void setMouseCoords(gfx::Coords relCoords);
		void setPrevCoords(gfx::Coords relPrevCoords);

		void setCanvasColour(gfx::Colour colour);
		void setPrimaryColour(gfx::Colour colour);
		void setSecondaryColour(gfx::Colour colour);
		gfx::Colour getPrimaryColour() const { return primaryColour_; }
		gfx::Colour getSecondaryColour() const { return secondaryColour_; }
		uint8_t* getPrimaryRGBA() { return primaryRGBA_; }
		uint8_t* getSecondaryRGBA() { return secondaryRGBA_; }
		
		bool isPrimaryActive() const { return primaryActive_; }
		void setIfPrimaryColourActive(const bool b) { primaryActive_ = b; }

		void updateAllToolsRGBA();

		//void setColor(SDL_Surface* surface);
		void draw(win::SDLRenderer* renderer) override;
		void updateAndRerender(win::SDLRenderer* renderer) override;
		void clearWindow() const;

		void setStartCoord(gfx::Coords startCoords);
		std::shared_ptr<ShapeTool> getShapeTool() const { return shapeTool_; }
		
	private:
		win::SDLRenderer* renderer_;
		bool renderTempTexture_;
		
		std::shared_ptr<Tool> activeTool_;
		std::shared_ptr<Tool> drawTool_;
		std::shared_ptr<ShapeTool> shapeTool_;
		
		gfx::Colour primaryColour_;
		gfx::Colour secondaryColour_;
		std::vector<gfx::Coords> clickedPixels_;
		gfx::Coords mouseCoords_;
		gfx::Coords prevMouseCoords_;
		gfx::Coords startCoord_;
		std::vector<gfx::Line> lines_;

		//whenever the active colour is changed this should be updated
		bool primaryActive_;
		uint8_t primaryRGBA_[4];
		uint8_t secondaryRGBA_[4];

		//For reference, as DrawWindow is  Window, backgroundColour is used as the canvas colour
	};
}