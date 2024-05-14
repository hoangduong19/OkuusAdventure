#pragma once
#include "Entity.h"
#include "Pipe.h"
class PowerUp : public Entity
{
private:
	Uint32 cooldownDuration;
	Uint32 lastActivationTime;
public:
	PowerUp();
	int getRandY();
	void speed();
	bool isOffScreen();
	bool isSkillReady();
	void activateCooldown();
	void Render(SDL_Renderer* renderer);
};