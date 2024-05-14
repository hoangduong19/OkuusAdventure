#pragma once
#include <iostream>
#include <sdl.h>
#include <SDL_image.h>
class TextureManager
{
public:
	static SDL_Texture* Loadtexture(const char* filepath, SDL_Renderer* renderer);
};