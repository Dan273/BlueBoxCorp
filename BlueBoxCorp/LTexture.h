#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

class LTexture
{
public:
	static SDL_Texture* LoadTexture(const char* texture, SDL_Renderer* ren);
};

