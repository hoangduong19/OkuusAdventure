#include "Bird.h"
#include "define.h"
const double deltatime = 1.0 / 30;
const double gravity = 0.25;
Bird::Bird()
{
	velY = 0;
	frame = 0;
	timeFrame = 0;
	angle_ = 0;
	playing = false;
}
void Bird::HandleGravity()
{
	if (playing)
	{
		int y = this->getDest().y ;
		velY += gravity;//gravity simulation, cang trong trang thai roi thi roi cang nhanh
		y += velY;//hieu ung chim roi nhanh hon
		angle_ = (velY / 2) * 15;//cap nhat angle theo velY->stable
		if (y < 0) y = 0;
		this->setDest(this->getDest().x, y, this->getDest().w, this->getDest().h);
	}
}
void Bird::HandleFly()
{
	playing = true;
	velY = -5;//reset lai velY ve trang thai ban dau khi nhan space
	this->getDest().y += velY * deltatime;
}
void Bird::FellGround(bool& is_on_ground)
{
	if (!is_on_ground)
	{
		int y = this->getDest().y ;
		y += 5;
		angle_ = (y / 2) ;
		this->setDest(this->getDest().x, y, this->getDest().w, this->getDest().h);
	}
	if (this->getDest().y + this->getDest().h >= Ground_Height)
	{
		is_on_ground = true;
	}
}
void Bird::Render(SDL_Renderer* renderer)
{
	SDL_RenderCopyEx(renderer, getTexture(), &getSrc(), &getDest(), angle_, NULL, SDL_FLIP_NONE);
}
void Bird::SetAngle(int angle)
{
	angle_ = angle;
}
