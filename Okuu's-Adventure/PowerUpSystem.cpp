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
void PowerUp::activateCooldown(bool& skill_ready)
{
	lastActivationTime = SDL_GetTicks();//lay moc thoi gian hien tai
	skill_ready = false;
}
bool PowerUp::isSkillReady(bool& skill_ready) {
	Uint32 currentTime = SDL_GetTicks();
	//if (currentTime == 0) return true;
	if (skill_ready) return true;
	if ((currentTime - lastActivationTime) >= cooldownDuration)
	{
		skill_ready = true;
		return true;
	}
	return false;
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
