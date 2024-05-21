#pragma once
#include "TextureManager.h"
#include "Entity.h"
#include "TextObject.h"
Entity::Entity() {}
void Entity::setSrc(int x, int y, int w, int h)
{
	src.x = x;
	src.y = y;
	src.w = w;
	src.h = h;
}
void Entity::setDest(int x, int y, int w, int h)
{
	dest.x = x;
	dest.y = y;
	dest.w = w;
	dest.h = h;
}
SDL_Rect& Entity::getSrc()
{
	return src;
}
SDL_Rect& Entity::getDest()
{
	return dest;
}
void Entity::CreateTexture(const char* filepath, SDL_Renderer* renderer)
{
	tex = TextureManager::Loadtexture(filepath, renderer);
}
SDL_Texture* Entity::getTexture()
{
	return tex;
}
void Entity::CreateTextfromTexture(const char* textpath, int size, std::string textToWrite, SDL_Color color, SDL_Renderer* renderer)
{
	texFromText = TextObject::loadText(textpath, size, textToWrite, color, renderer);//xai static thay cho tao 1 bien class(vd text) roi dung 1 text.loadtext
}
SDL_Texture* Entity::getText()
{
	return texFromText;
}
