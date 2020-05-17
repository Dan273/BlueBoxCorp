#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <cmath>

class LTexture
{
public:
public:
	//Initializes variables
	LTexture();

	//Deallocates memory
	~LTexture();

	static SDL_Texture* LoadTexture(const char* texture, SDL_Renderer* ren);


private:
	//The actual hardware texture
	SDL_Texture* mTexture;
};

