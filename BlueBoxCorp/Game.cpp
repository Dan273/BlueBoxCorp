#include "Game.h"
#include "Collider.h"
#include "LTexture.h"

int WIDTH, HEIGHT;
int levelWIDTH = 1024, levelHEIGHT = 720;

SDL_Rect camera = { 0, 0, WIDTH, HEIGHT };

LTexture bgTexture;

GameObject* playerObject;
GameObject* ground;
GameObject* crate;

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
			SDL_SetRenderDrawColor(renderer, 25, 25, 25, 255);
			std::cout << "Renderer Created!" << std::endl;
		}
		isRunning = true;
	}

	bgTexture.SetColor(255, 255, 255);
	bgTexture.LoadTexture("Assets/Background.png", renderer);

	//Spawn Player
	Transform* playerTransform = new Transform("Assets/Sprites/Player_Front.png", renderer, new Vector2(width / 2, 0), new Vector2(64, 128));
	playerObject = new GameObject("Player", playerTransform, true);

	//Spawn Ground
	Transform* groundTransform = new Transform("Assets/Sprites/Ground.png", renderer, new Vector2(0, height - 128), new Vector2(width*2, 128));
	ground = new GameObject("Ground", groundTransform, true);

	//Spawn Crate
	Transform* crateTransform = new Transform("Assets/Sprites/crate.png", renderer, new Vector2(width/2, height - groundTransform->scale->y*1.5), new Vector2(64, 64));
	crate = new GameObject("Box", crateTransform, true);
}

int xVel = 0;
int yVel = 0;
bool canJump = false;
void Game::HandleEvents()
{
	//Handle the player movement
	int speed = 5;
	int maxSpeed = 5;
	int jumpHeight = 50;
	int gravity = -9;

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
			canJump = false;
			yVel -= speed;
			break;
		case SDLK_DOWN:
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
	}

	playerObject->transform->position->x += xVel;
	playerObject->transform->position->y += yVel;

	camera.x++;

	//Gravity pulls the player to the ground
	//playerObject->transform->position->y -= gravity;

	//Collide with things
	if (playerObject->transform->position->x < 0 || playerObject->transform->position->x + playerObject->transform->scale->x > WIDTH ||
			Collider::CheckCollision(playerObject->transform, ground->transform) || Collider::CheckCollision(playerObject->transform, crate->transform)) {
		playerObject->transform->position->x -= xVel;
	}
	if (playerObject->transform->position->y < 0 || playerObject->transform->position->y + playerObject->transform->scale->y > HEIGHT ||
			Collider::CheckCollision(playerObject->transform, ground->transform) || Collider::CheckCollision(playerObject->transform, crate->transform)) {
		playerObject->transform->position->y -= yVel;
	}
}

void Game::Update()
{
	playerObject->transform->Update();
	ground->transform->Update();
	crate->transform->Update();
}

void Game::Render()
{	
	//Center the camera over the dot
	camera.x = (playerObject->transform->position->x + playerObject->transform->scale->x / 2) - WIDTH / 2;
	camera.y = (playerObject->transform->position->y + playerObject->transform->scale->y / 2) - HEIGHT / 2;

	//Keep the camera in bounds
	if (camera.x < 0)
	{
		camera.x = 0;
	}
	if (camera.y < 0)
	{
		camera.y = 0;
	}
	if (camera.x > levelWIDTH - camera.w)
	{
		camera.x = levelWIDTH - camera.w;
	}
	if (camera.y > levelHEIGHT - camera.h)
	{
		camera.y = levelHEIGHT - camera.h;
	}

	SDL_RenderClear(renderer);

	bgTexture.Render(0, 0, &camera);

	playerObject->transform->Render(camera.x, camera.y);
	ground->transform->Render(camera.x, camera.y);
	crate->transform->Render(camera.x, camera.y);

	SDL_RenderPresent(renderer);
}

void Game::Clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleaned!" << std::endl;
}