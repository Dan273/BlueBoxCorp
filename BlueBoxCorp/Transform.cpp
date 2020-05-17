#include "Transform.h"
#include "LTexture.h"

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

void Transform::Render(int camX, int camY)
{
	texture.Render(position->x - camX, position->y - camY);
	SDL_RenderCopy(renderer, objTexture, &srcRect, &destRect);
}