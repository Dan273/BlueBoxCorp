#include "Game.h"
#include "Collider.h"
#include "LTexture.h"

int WIDTH, HEIGHT;

GameObject* player;
GameObject* crate;
GameObject* bulletHolder;

Time time;

Game::Game()
{}

Game::~Game()
{}

void Game::init(const char *title, int xPos, int yPos, int width, int height, bool fullscreen)
{
	//Start the timer
	time.Start();

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
	Transform* playerTransform = new Transform("Assets/Sprites/Player.png", renderer, new Vector2(width / 2, height/2), new Vector2(64, 128));
	player = new GameObject("Player", playerTransform);

	//Spawn Crate
	Transform* crateTransform = new Transform("Assets/Sprites/crate.png", renderer, new Vector2(width/2, 0), new Vector2(64, 64));
	crate = new GameObject("Box", crateTransform);
}

int xVel = 0;
int yVel = 0;
bool canJump = false;
void Game::HandleEvents()
{
	//Handle the player movement
	int speed = 5;
	int maxSpeed = 5;

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
			if (xVel > -maxSpeed)
				xVel -= speed;
			break;
		case SDLK_RIGHT:
			if (xVel < maxSpeed)
				xVel += speed;
			break;
		case SDLK_UP:
			yVel -= speed;
			break;
		case SDLK_DOWN:
			yVel += speed;
			break;
		default:
			break;
		}

		//Check if we press the shoot key
		if (event.key.keysym.scancode == SDL_SCANCODE_LCTRL) 
		{
			//Temporary - Move into its own function
			//Set bullet transform
			Transform* bullet = new Transform("Assets/Sprites/Laser.png", renderer,
												new Vector2(player->transform->position->x + player->transform->scale->x/2, 
															player->transform->position->y),
												new Vector2(8, 16));
			bulletHolder = new GameObject("Bullet", bullet);
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
	}

	//Move player based on the velocity
	player->transform->position->x += xVel;
	player->transform->position->y += yVel;

	//If we have a bullet then move the bullet based on its force
	if(bulletHolder != nullptr && bulletHolder->transform != nullptr)
		bulletHolder->transform->position->y--;

	//Collide with things
	if (player->transform->position->x < 0 || player->transform->position->x + player->transform->scale->x > WIDTH ||
			Collider::CheckCollision(player->transform, crate->transform)) {
		player->transform->position->x -= xVel;
	}
	if (player->transform->position->y < 0 || player->transform->position->y + player->transform->scale->y > HEIGHT ||
			Collider::CheckCollision(player->transform, crate->transform)) {
		player->transform->position->y -= yVel;
	}
}

void Game::Update()
{
	player->transform->Update();
	crate->transform->Update();
	if(bulletHolder != nullptr && bulletHolder->transform != nullptr)
		bulletHolder->transform->Update();
}

void Game::Render()
{	
	SDL_RenderClear(renderer);


	player->transform->Render();
	crate->transform->Render();

	if (bulletHolder != nullptr && bulletHolder->transform != nullptr)
		bulletHolder->transform->Render();

	SDL_RenderPresent(renderer);
}

void Game::Clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleaned!" << std::endl;
}