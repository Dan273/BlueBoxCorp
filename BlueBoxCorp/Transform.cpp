#include "Transform.h"
#include <iostream>

Transform::Transform(const char* text, SDL_Renderer* ren, Vector2* pos, Vector2* s)
{
	renderer = ren;
	objTexture = LTexture::LoadTexture(text, ren);

	position = pos;
	scale = s;
}

void Transform::Update()
{
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = scale->x;
	srcRect.h = scale->y;

	destRect.x = position->x;
	destRect.y = position->y;
	destRect.w = srcRect.w;
	destRect.h = srcRect.h;
}

void Transform::Render()
{
	SDL_RenderCopy(renderer, objTexture, &srcRect, &destRect);
}

void Transform::Destroy()
{
	SDL_DestroyTexture(objTexture);
	std::cout << "Transform Destroyed!" << std::endl;
}