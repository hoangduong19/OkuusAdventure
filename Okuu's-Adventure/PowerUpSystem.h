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
	bool isSkillReady(bool& skill_ready);
	void activateCooldown(bool& skill_ready);
	void Render(SDL_Renderer* renderer);
};
