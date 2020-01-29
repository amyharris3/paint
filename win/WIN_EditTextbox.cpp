#include "WIN_EditTextbox.h"
#include "SDL.h"
#include "SDL_ttf.h"

using namespace win;

EditTextbox::EditTextbox(gfx::Rectangle rect, const char* name, SDL_Renderer* renderer, int const textSize, int const xOffset, int const yOffset, std::shared_ptr<int> linkedVariable)
	: UIelement(rect, name)
	, renderer_(renderer)
	, text_(renderer, { 0, 0, 0, 0xFF }, "OpenSans-Bold.ttf", textSize,"100")
	, xOffset_(xOffset)
	, yOffset_(yOffset)
	, linkedVariable_(std::move(linkedVariable))
{
	setBackgroundColour(gfx::Colour(255, 255, 255, 255));

}

void EditTextbox::draw()
{
	SDL_Rect boxRect = { getRect().x, getRect().y, getRect().width, getRect().height };
	uint8_t rgba[4];
	getBackgroundColour().getComponents(rgba);
	SDL_SetRenderDrawColor(renderer_, rgba[0], rgba[1], rgba[2], rgba[3]);
	SDL_RenderFillRect(renderer_, &boxRect);
	
	auto renderSuccess = text_.renderText(getRect().x + xOffset_, getRect().y + yOffset_);
	


}
