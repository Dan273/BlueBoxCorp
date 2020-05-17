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

	//Loads image at specified path
	bool LoadFromFile(const char* path);

#if defined(_SDL_TTF_H) || defined(SDL_TTF_H)
	//Creates image from font string
	bool LoadFromRenderedText(std::string textureText, SDL_Color textColor);
#endif

	//Deallocates texture
	void Free();

	//Set color modulation
	void SetColor(Uint8 red, Uint8 green, Uint8 blue);

	//Set blending
	void SetBlendMode(SDL_BlendMode blending);

	//Set alpha modulation
	void SetAlpha(Uint8 alpha);

	//Renders texture at given point
	void Render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	//Gets image dimensions
	int GetWidth();
	int GetHeight();

private:
	//The actual hardware texture
	SDL_Texture* mTexture;

	//Image dimensions
	int mWidth;
	int mHeight;
};

