#include "PowerUpSystem.h"
#include <cstdlib>
#include <ctime>
const double deltatime = 1.0 / 30;
PowerUp::PowerUp()
{
	srand(time(NULL));
	cooldownDuration = 15000;
	lastActivationTime = 0;
}
void PowerUp::activateCooldown()
{
	lastActivationTime = SDL_GetTicks();
}
bool PowerUp::isSkillReady() {
	Uint32 currentTime = SDL_GetTicks();
	return (currentTime - lastActivationTime) >= cooldownDuration;
}
int PowerUp::getRandY()
{
	return rand() % 2 == 0 ? 100 : 400;
}
void PowerUp::speed()
{
	double x = this->getDest().x;
	x -= 60 * deltatime;
	this->setDest(x, this->getDest().y, this->getDest().w, this->getDest().h);
}
bool PowerUp::isOffScreen()
{
	if (this->getDest().x + this->getDest().w <=0)
	{
		return true;
	}
	return false;
}
void PowerUp::Render(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, getTexture(), NULL, &getDest());
}