#pragma once

#include "Vector2.h"
#include "SDL_image.h"
#include "LTexture.h"

class Transform
{
public:
	Transform(const char* text, SDL_Renderer* ren, Vector2* pos, Vector2* s);
	~Transform();

	Vector2* position;
	Vector2* scale;

	void Update();
	void Render(int camX, int camY);

private:
	LTexture texture;
	SDL_Renderer* ren;
	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;
	SDL_Renderer* renderer;
};

