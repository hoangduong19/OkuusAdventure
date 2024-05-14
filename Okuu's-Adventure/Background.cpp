#include "Background.h"
const double deltatime = 1.0 / 30;
Background::Background()
{
	x1 = 0;
	x2 = -539;
}
void Background::scrolling1()
{
	if (x1 < -538) // If the image has moved off the screen
	{
		x1 = 538; // Reset its position to the right side of the screen
	}
	x1 -= 60*deltatime;
	Entity::setDest(x1, Entity::getDest().y, Entity::getDest().w, Entity::getDest().h);
}
void Background::scrolling2()
{
	if (x2 < -538) // If the image has moved off the screen
	{
		x2 = 538; // Reset its position to the right side of the screen
	}
	x2 -= 60*deltatime;
	Entity::setDest(x2, Entity::getDest().y, Entity::getDest().w, Entity::getDest().h);
}
void Background::Render(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, getTexture(), &getSrc(), &getDest());
}