#pragma once
#include <sdl.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Entity.h"
#include <iostream>
class TextObject : public Entity
{
private:
public:
	static SDL_Texture* loadText(const char* textpath, int size, std::string textToWrite, SDL_Color color, SDL_Renderer* renderer);
	void RenderText(SDL_Renderer* renderer);
	void destroy_old_score();
};