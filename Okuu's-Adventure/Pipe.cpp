#include "Pipe.h"
#include "define.h"
#include <cstdlib>
#include <ctime>
const double deltatime = 1.0 / 30; //khoang thoi gian giua 2 khung hinh lien tiep, giup game chay muot tren moi thiet bi
								//neu khong su dung deltatime fps se thinh thoang bi tut, khien game ko muot 
								// va su dung deltatime co the giup chung ta ko can phai uoc luong, tu tin su dung dung unit
Pipe::Pipe()
{
	speed = 1;
	maxTop = false; 
	maxBot = false;
	srand(time(NULL));
}
void Pipe::Up()
{
	if (this->getDest().x + this->getDest().w < Screen_Width)
	{
		double yTop = this->getDest().y;
		if (!maxTop)
		{
			yTop += 30 * deltatime;
			if (yTop >= 0) maxTop = true;
		}
		else {
			yTop -= 30 * deltatime;
			if (yTop <= -165) maxTop = false;
		}
		this->setDest(this->getDest().x, yTop, this->getDest().w, this->getDest().h);
	}
}
void Pipe::Down()
{
	if (this->getDest().x + this->getDest().w < Screen_Width)
	{
		double yBot = this->getDest().y;
		if (!maxBot)
		{
			yBot += 30 * deltatime;
			if (yBot >= 495) maxBot = true;
		}
		else {
			yBot -= 30 * deltatime;
			if (yBot <= 330) maxBot = false;
		}
		this->setDest(this->getDest().x, yBot, this->getDest().w, this->getDest().h);
	}
}
void Pipe::speedup(double acceleration)
{
	double x = this->getDest().x;
	x -= acceleration*deltatime;//deltatime = seconds/frame, moi lan render la 30 khung hinh/1s,
	this->setDest(x, Entity::getDest().y, this->getDest().w, Entity::getDest().h);
}
bool Pipe::isOffScreen()
{
	if (this->getDest().x + this->getDest().w <= 0) return true;
	return false;
}

int Pipe::getRand()
{
	return rand() % (305 - 140) + 140;//pipeHeight = 250
}
void Pipe::Render(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, getTexture(), &getSrc(), &getDest());
}