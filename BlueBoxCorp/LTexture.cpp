#include "LTexture.h"

//Simply do all of the texture loading through here
SDL_Texture* LTexture::LoadTexture(const char* texture, SDL_Renderer* ren)
{
	SDL_Surface* tempSurface = IMG_Load(texture);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, tempSurface);
	SDL_FreeSurface(tempSurface);

	return tex;
}