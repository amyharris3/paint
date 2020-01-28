#pragma once

#include "WIN_Window.h"
#include "PAINT_DrawTool.h"


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
	// JG: Coords.h? Vector2.h? 
	struct Coords
	{
		int x;
		int y;
	};



	class Colour;
	class Tool;
	class Brush;

	class DrawWindow final :
		public win::Window
	{
	private:
		// TODO What sort of pointer?
		std::shared_ptr<Tool> activeTool_;
		const char* name_;  
		gfx::Colour primaryColour_;
		gfx::Colour secondaryColour_;
		SDL_Renderer* renderer_;
		SDL_Texture* texture_;
		bool drawToggle_;
		Coords mouseCoords_;
		Coords prevMouseCoords_;

		std::shared_ptr<Tool> drawTool_;
		


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
		//void setActiveBrush(std::shared_ptr<Brush> brush);
		void setActiveTool(std::shared_ptr<Tool> tool);
		void activateDrawTool();
		//void getPixels(SDL_Surface* surface);
		void setMouseCoords(Coords relCoords);
		void setPrevCoords(Coords relPrevCoords);

		gfx::Colour getPrimaryColour() const { return primaryColour_; }
		gfx::Colour getSecondaryColour() const { return secondaryColour_; }
		void setPrimaryColour(gfx::Colour colour);
		void setSecondaryColour(gfx::Colour colour);
		void swapColours();

		//void setColor(SDL_Surface* surface);
		void draw() override;
	};
}