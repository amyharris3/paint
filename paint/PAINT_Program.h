#pragma once

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Surface;
struct SDL_Texture;

namespace paint
{
	class Screen;

	class Program
	{
	public:
		Program();
		~Program() = default;
		Program(Program const& that) = default;
		Program(Program&& that) = default;
		Program& operator=(Program const& that) = default;
		Program& operator=(Program&& that) = default;

		void initialize(SDL_Renderer* renderer);
		void run() const;

	private:
		std::shared_ptr<Screen> screen_;
		SDL_Renderer* renderer_;
	};
}
