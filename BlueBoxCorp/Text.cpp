#include "Text.h"
#include "Game.h"

Text::Text(const std::string &t, const char* fontName, int fontSize, SDL_Color c, SDL_Renderer* ren, int w)
{
	texture = LoadFont(t, fontName, fontSize, c, ren, w);

	SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
}

Text::~Text()
{}

SDL_Texture* Text::LoadFont(const std::string &t, const char* fontName, int fontSize, SDL_Color c, SDL_Renderer* ren, int w)
{
	//Set the font of the text
	TTF_Font* newFont = TTF_OpenFont(fontName, fontSize);
	if (!newFont)
		std::cout << "Failed to load font!" << std::endl;

	//Set the surface for the text
	SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(newFont, t.c_str(), c, w);
	if (!textSurface)
		std::cout << "Failed to load surface!" << std::endl;

	//Set the text as a texture
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(ren, textSurface);
	if (!textTexture)
		std::cout << "Failed to load texture!" << std::endl;

	SDL_FreeSurface(textSurface);
	TTF_CloseFont(newFont);

	return textTexture;
}

void Text::Render(int x, int y, SDL_Renderer* ren) const 
{
	rect.x = x;
	rect.y = y;

	SDL_RenderCopy(ren, texture, NULL, &rect);

	//Because all text will be updated on every frame, we need to destroy the old texture every frame to prevent memeory loss
	SDL_DestroyTexture(texture);
}