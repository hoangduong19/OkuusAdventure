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
	const char* pathBird[2] = { "rsc/okuu_aftercut.png", "rsc/okuu_with_shield.png"};
	int frame;
	double timeFrame;
	double angle_;
	bool playing;
};