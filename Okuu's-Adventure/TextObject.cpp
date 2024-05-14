#include "TextObject.h"
SDL_Texture* TextObject::loadText(const char* textpath, int size, std::string textToWrite, SDL_Color color, SDL_Renderer* renderer)
{
	TTF_Font* font = TTF_OpenFont(textpath, size);
	SDL_Surface* surface = TTF_RenderText_Solid(font, textToWrite.c_str(), color);
	if (surface == NULL)
	{
		std::cout << "Failed to load font! Error: " << SDL_GetError() << std::endl;
	}
	SDL_Texture* texFromText = SDL_CreateTextureFromSurface(renderer, surface);
	if (texFromText == NULL)
	{
		std::cout << "Failed to create texture! Error: " << SDL_GetError() << std::endl;
	}
	SDL_FreeSurface(surface);
	return texFromText;
}
void TextObject::destroy_old_score()
{
	SDL_DestroyTexture(this->getTexture());
}
void TextObject::RenderText(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, getText(), NULL, &getDest());
}