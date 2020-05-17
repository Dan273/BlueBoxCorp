#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Transform.h"
#include "Vector2.h"
#include "GameObject.h"
#include "Time.h";

class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen);
	
	void HandleEvents();
	void Update();
	void Render();
	void Clean();
	
	bool Running() { return isRunning; }

private:
	int cnt = 0 ;
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;
};