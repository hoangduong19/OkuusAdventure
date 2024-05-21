#include "TextureManager.h"
SDL_Texture* TextureManager::Loadtexture(const char* filepath, SDL_Renderer* renderer)
{
	SDL_Surface* surface;//bao gom do phan giai, dinh dang pixel, du lieu pixel
	surface = IMG_Load(filepath);
	if (surface == NULL)
	{
		std::cout << "Failed to load image! Error: " << SDL_GetError() << std::endl;
	}
	SDL_Texture* tex;
	tex = SDL_CreateTextureFromSurface(renderer, surface);
	if (tex == NULL)
	{
		std::cout << "Failed to create texture! Error: " << SDL_GetError() << std::endl;
	}
	SDL_FreeSurface(surface);
	return tex;
}
