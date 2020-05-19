#include "Game.h"

int WIDTH, HEIGHT;

PlayerManager* player;

Transform* background;

const Uint8* keystates = SDL_GetKeyboardState(NULL);

Game::Game()
{}

Game::~Game()
{}

void Game::init(const char *title, int xPos, int yPos, int width, int height, bool fullscreen)
{
	WIDTH = width;
	HEIGHT = height;

	int flags = 0;
	if (fullscreen) 
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "SDL could not initialise! SDL Error: " << SDL_GetError() << std::endl;
		isRunning = false;
	}
	else 
	{
		window = SDL_CreateWindow(title, xPos, yPos, width, height, flags);
		if (window)
		{
			std::cout << "Window Created!" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			//Currently: White
			SDL_SetRenderDrawColor(renderer, 0, 0, 25, 255);
			std::cout << "Renderer Created!" << std::endl;
		}
		isRunning = true;
	}

	//Spawn Player
	Transform* playerTransform = new Transform("Assets/Sprites/Player.png", renderer, new Vector2(width / 2, height/1.5f), new Vector2(64, 128));
	player = new PlayerManager(playerTransform, 250, 100, 0, 0, 0);

	//Spawn Background
	background = new Transform("Assets/Background.png", renderer, new Vector2(0, 0), new Vector2(width, height));
}

int xVel = 0;
int yVel = 0;
bool canJump = false;
void Game::HandleEvents()
{
	//Handle the player movement
	int speed = 4;
	int maxSpeed = 4;

	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	}

	if (event.type == SDL_KEYDOWN)
	{
		//Check the SDLKey values and move change the coords
		switch (event.key.keysym.sym) {
		case SDLK_LEFT:
			if (xVel >= -maxSpeed)
				xVel -= speed;
			break;
		case SDLK_RIGHT:
			if (xVel <= maxSpeed)
				xVel += speed;
			break;
		case SDLK_UP:
			if(yVel >= -maxSpeed)
				yVel -= speed;
			break;
		case SDLK_DOWN:
			if(yVel <= maxSpeed)
				yVel += speed;
			break;
		default:
			break;
		}
	}
	if(event.type == SDL_KEYUP)
	{
		switch (event.key.keysym.sym) {
		case SDLK_LEFT:
			if (xVel < 0)
				xVel = 0;
			break;
		case SDLK_RIGHT:
			if (xVel > 0)
				xVel = 0;
			break;
		case SDLK_UP:
			if (yVel < 0)
				yVel = 0;
			break;
		case SDLK_DOWN:
			if (yVel > 0)
				yVel = 0;
			break;
		default:
			break;
		}

		if (event.key.keysym.scancode == SDL_SCANCODE_LCTRL)
		{
			hasShot = false;
		}
	}

	//Check if we press the shoot key
	if (keystates[SDL_SCANCODE_LCTRL] && !hasShot)
	{
		hasShot = true;
		//Shoot the basic projectile via the function created
		Shooting().Shoot(Shooting().projectileTypes[0], 1, renderer,
			new Vector2(player->transform->position->x + player->transform->scale->x / 2 -
				Shooting().projectileTypes[0]->scale->x / 2,
				player->transform->position->y));
	}
	
	//Temp - Spawn enemy when we press space
	if (keystates[SDL_SCANCODE_SPACE])
	{
		//Spawn enemy
		EnemySpawner().SpawnEnemy(EnemySpawner().enemyTypes[0], new Vector2(rand() % (WIDTH - 0 + 1) + 0, 0), renderer);
	}

	//Move player based on the velocity
	player->transform->position->x += xVel;
	player->transform->position->y += yVel;

	//Collide with things
	if (player->transform->position->x < 0 || player->transform->position->x + player->transform->scale->x > WIDTH) {
		player->transform->position->x -= xVel;
	}
	if (player->transform->position->y < 0 || player->transform->position->y + player->transform->scale->y > HEIGHT) {
		player->transform->position->y -= yVel;
	}
}

void Game::Update()
{
	background->Update();
	EnemySpawner().Update(HEIGHT);
	player->transform->Update();
	Shooting().Update(WIDTH, HEIGHT);
}

void Game::Render()
{	
	SDL_RenderClear(renderer);

	background->Render();
	EnemySpawner().Render();
	player->transform->Render();
	Shooting().Render();
	
	SDL_RenderPresent(renderer);
}

void Game::Clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleaned!" << std::endl;
}