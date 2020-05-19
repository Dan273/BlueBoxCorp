#pragma once
#include <iostream>
#include <string>
#include "SDL.h"
#include "SDL_ttf.h"

class Text
{
public:
	Text(const std::string &t, const char* fontName, int fontSize, SDL_Color c, SDL_Renderer* ren);

	SDL_Texture* LoadFont(const std::string &t, const char* fontName, int fontSize, SDL_Color c, SDL_Renderer* ren);

	void Render(int x, int y, SDL_Renderer* ren) const;

private:
	SDL_Texture* texture = nullptr;
	mutable SDL_Rect rect;
};

