#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Entity.h"
class GUIObject : public Entity
{
private: int frameTimer; int frame;
public:
	GUIObject();
	void updateFrame( int totalFrame, int DelayTime, SDL_Renderer*renderer, const char* filepath[]);
	void Render( SDL_Renderer* renderer);
};