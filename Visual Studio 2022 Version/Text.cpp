#include "Text.h"

Text::Text(SDL_Renderer*& render) {
	TTF_Init();
	this->render = render;
}

Text::~Text() {
	TTF_Quit();
}

void Text::Clear_Texture_Surface() {
	TTF_CloseFont(font);
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}

void Text::Get_Text(std::string str, int fontType, int fontSize, SDL_Color color) {
	font = TTF_OpenFont(fontType == 0 ? "./fonts/times.ttf" : fontType == 1 ? "./fonts/Minecraft.ttf" : "./fonts/IndieFlower-Regular.ttf", fontSize);
	if (font == nullptr) throw TEXT_EXCEPTION("Couldn't find/init open ttf font.");

	surface = TTF_RenderText_Solid(font, str.c_str(), color);
	if (surface == nullptr) throw TEXT_EXCEPTION("Couldn't create Surface!");

	texture = SDL_CreateTextureFromSurface(render, surface);
	if (texture == nullptr) throw TEXT_EXCEPTION("Couldn't create TextTexture!");
}

void Text::Copy_Text(int x, int y) {
	to = { x, y, surface->w, surface->h };
	SDL_RenderCopy(render, texture, NULL, &to);
}

void Text::Copy_Text_Centered(int x, int y) {
	to = { x - surface->w / 2, y - surface->h / 2, surface->w, surface->h };
	SDL_RenderCopy(render, texture, NULL, &to);
}

void Text::Copy_Text_YCentered(int x, int y) {
	to = { x, y - surface->h / 2, surface->w, surface->h };
	SDL_RenderCopy(render, texture, NULL, &to);
}

void Text::Render_Text(std::string str, int fontType, int fontSize, SDL_Color color, int x, int y) {
	Get_Text(str, fontType, fontSize, color);
	Copy_Text(x, y);
	Clear_Texture_Surface();
}

void Text::Render_Text_Centered(std::string str, int fontType, int fontSize, SDL_Color color, int x, int y) {
	Get_Text(str, fontType, fontSize, color);
	Copy_Text_Centered(x, y);
	Clear_Texture_Surface();
}

void Text::Render_Text_YCentered(std::string str, int fontType, int fontSize, SDL_Color color, int x, int y) {
	Get_Text(str, fontType, fontSize, color);
	Copy_Text_YCentered(x, y);
	Clear_Texture_Surface();
}

int Text::Check_Length(std::string str, int fontType, int fontSize) {
	Get_Text(str, fontType, fontSize, { 255,255,255,255 });
	int length = surface->w;
	Clear_Texture_Surface();
	return length;
}