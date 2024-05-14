#include "GUIObject.h"
GUIObject::GUIObject()
{
	frameTimer = 0;
	frame = 0;
}
void GUIObject::updateFrame(int totalFrame, int DelayTime, SDL_Renderer* renderer, const char* filepath[])
{
	if (frameTimer <= 0) { // FrameTimer dung de delay animation, neu het Frametimer thi animation ke tiep moi dc render
		if (frame >= totalFrame - 1) frame = 0;
		else frame++;

		frameTimer = DelayTime;
	}
	else {
		frameTimer--;
	}
	SDL_Texture* oldTexture = this->getTexture();
	this->CreateTexture(filepath[frame], renderer);
	this->Render(renderer);
	SDL_DestroyTexture(oldTexture);
}
void GUIObject::Render(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, getTexture(), NULL, &getDest());
}