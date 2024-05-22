#pragma once
#include "Entity.h"
#include "Pipe.h"
#include <string>
class Bird : public Entity
{
public:
	Bird();
	void HandleFly();
	void HandleGravity();
	void FellGround(bool& is_on_ground);
	void Render(SDL_Renderer* renderer);
	void SetAngle(int angle);
private:
	float velY;
	double angle_;
	bool playing;
};
