#pragma once
#include "Entity.h"
#include <vector>
class Pipe : public Entity
{
public:
	Pipe();
	bool isOffScreen();
	void Render(SDL_Renderer* renderer);
	int getRand();
	void speedup(double acceleration);
	void Up();
	void Down();
private:
	bool maxTop, maxBot;
	std::vector <Pipe> pipes;
	double speed;
};