#pragma once
#include "Entity.h"
class Background : public Entity
{
private: int x1,x2;
public: 
	Background();
	void Render(SDL_Renderer* renderer);
	void scrolling1();
	void scrolling2();
};
