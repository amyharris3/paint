#pragma once
#include "WIN_UIelement.h"
#include "WIN_SDLRenderer.h"

struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Rect;

namespace win
{
	class SDLRenderer;

	class Button;
	
	class Button final:
		public UIelement
	{
	public:
		Button() = delete;
		Button(win::SDLRenderer* renderer, const gfx::Rectangle& rect, const char* name, const char* spritePath, ActionFunction act);
		virtual ~Button();
		Button(const Button& that) = default;
		Button(Button&& that) = default;
		Button& operator=(const Button& that) = default;
		Button& operator=(Button&& that) = default;
		void draw(win::SDLRenderer* renderer) override;
		bool mouseEnter(MouseButton button, bool clicked = false) override;
		bool mouseExit(MouseButton button, bool clicked = false) override;
		bool mouseMove(SDL_MouseMotionEvent& e) override;
		bool mouseButtonDown(MouseButton button, bool clicked = false) override;
		bool mouseButtonUp(MouseButton button, bool clicked = false, win::SDLRenderer* renderer = nullptr) override;

		ActionFunction action;

	private:
		win::SDLRenderer* renderer_;
		//SDL_Renderer* renderer_;
		SDL_Texture* texture_;
		gfx::Rectangle rect_;
		std::vector<SDL_Rect> spriteClips_;
		SDL_Rect* activeClip_;

		bool mouseDown_;
		bool mouseDragged_;
	};
}
