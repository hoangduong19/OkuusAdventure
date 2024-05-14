#pragma once
#include "TextureManager.h"
class Entity
{
private:
	SDL_Texture* tex;
	SDL_Texture* texFromText;
	SDL_Rect src, dest;
public:
	Entity();
	SDL_Texture* getTexture();
	SDL_Texture* getText();
	void setSrc(int x, int y, int w, int h);
	void setDest(int x, int y, int w, int h);
	SDL_Rect& getSrc();
	SDL_Rect& getDest();
	void CreateTexture(const char* filepath, SDL_Renderer* renderer);
	void CreateTextfromTexture(const char* textpath, int size, std::string textToWrite, SDL_Color color, SDL_Renderer* renderer);
};