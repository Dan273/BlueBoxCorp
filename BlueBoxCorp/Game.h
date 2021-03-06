#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include "Initial.h"
#include "Collider.h"
#include "Transform.h"
#include "Vector2.h"
#include "Time.h"
#include "LTexture.h"
#include "Shooting.h"
#include "EnemySpawner.h"
#include "PlayerManager.h"
#include "Text.h"

extern PlayerManager* player;
extern bool restart;

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
	void Delete();
	
	bool Running() { return isRunning; }

private:
	int cnt = 0;
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;
};