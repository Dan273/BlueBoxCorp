#include "Game.h"
#include <string>

int WIDTH, HEIGHT;

bool gameStarted;
bool gameOver;
bool restart;

PlayerManager* player;

Transform* background;

const Uint8* keystates = SDL_GetKeyboardState(NULL);

Text* gameText;
Text* scoreText;
Text* healthText;
Text* baseText;

int gameW;
int delay = 0;

const char* font = "Assets/ROBOTECH.ttf";

Game::Game()
{}

Game::~Game()
{}

void Game::init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen)
{
	gameStarted = false;
	gameOver = false;

	WIDTH = width;
	HEIGHT = height;

	gameW = width;

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
			//Currently: Grey/Blue
			SDL_SetRenderDrawColor(renderer, 0, 0, 25, 255);
			std::cout << "Renderer Created!" << std::endl;
		}
		isRunning = true;
	}

	TTF_Init();

	//Spawn Player
	Transform* playerTransform = new Transform("Assets/Sprites/Player.png", renderer, new Vector2(width / 2, height / 1.5f), new Vector2(64, 128));
	player = new PlayerManager(playerTransform, 100, 100, 0, 0, 0);

	//Spawn Background
	background = new Transform("Assets/Background.png", renderer, new Vector2(0, 0), new Vector2(width, height));

}

int xVel = 0;
int yVel = 0;
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

	//Check if we have started the game
	if (gameStarted)
	{
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
				if (yVel > -maxSpeed)
					yVel -= speed;
				break;
			case SDLK_DOWN:
				if (yVel < maxSpeed)
					yVel += speed;
				break;
			default:
				break;
			}
		}
		if (event.type == SDL_KEYUP)
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
		if (--delay <= 0)
		{
			if (keystates[SDL_SCANCODE_LCTRL])
			{
				hasShot = true;
				//Shoot the basic projectile via the function created
				Shooting().Shoot(Shooting().projectileTypes[0], 1, renderer,
					new Vector2(player->transform->position->x + player->transform->scale->x / 2 -
						Shooting().projectileTypes[0]->scale->x / 2,
						player->transform->position->y));
				delay = 35;
			}
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
		else
		{
			//Player will move down by itself
			if(!keystates[SDL_SCANCODE_UP])
				player->transform->position->y += 1;
		}
	}
	else
	{
		//If we press space and the game hasnt started, then start
		if (keystates[SDL_SCANCODE_SPACE])
		{
			delete gameText;
			gameStarted = true;
		}
	}
		//If the player wants to restart, they can do so with a key input
	if (keystates[SDL_SCANCODE_R])
	{
		Initial().StartGame();
	}

	if (gameOver) 
	{
		//Player can quit with a key input
		if (keystates[SDL_SCANCODE_ESCAPE])
		{
			Initial().QuitGame();
		}
	}
}

void Game::Update()
{
	if (gameOver)
	{
		gameText = new Text("Game Over!\nScore: " + std::to_string(player->score) + " \nPress 'r' to restart!", 
								font, 32, { 255, 50, 50 }, renderer, gameW);
	}
	else
	{
		//Game Elements
		background->Update();
		if (gameStarted)
		{
			EnemySpawner().Update(HEIGHT, renderer, WIDTH);
			player->transform->Update();
			Shooting().Update(WIDTH, HEIGHT);
		}

		//UI Elements
		if (!gameStarted)
			gameText = new Text("Press 'space' to start...", font, 32, { 100, 255, 100 }, renderer, gameW);
		
		scoreText = new Text("Score: " + std::to_string(player->score), font, 32, { 255, 255, 255 }, renderer, WIDTH);
		healthText = new Text("Health: " + std::to_string(player->health), font, 32, { 255, 255, 255 }, renderer, WIDTH);
		baseText = new Text("Base Health: " + std::to_string(player->baseHealth), font, 32, { 255, 255, 255 }, renderer, WIDTH);
	}

	//If the player or the base health is 0 or below, game over
	if (player->health <= 0 || player->baseHealth <= 0)
	{
		gameOver = true;
		gameStarted = false;
	}
}

void Game::Render()
{
	SDL_RenderClear(renderer);

		background->Render();
	if (!gameOver)
	{
		EnemySpawner().Render();
		player->transform->Render();
		Shooting().Render();

		scoreText->Render(20, 20, renderer);
		healthText->Render(20, HEIGHT - 40, renderer);
		baseText->Render(WIDTH / 2, HEIGHT - 40, renderer);
	}

	if (!gameStarted)
		gameText->Render(WIDTH / 4, HEIGHT / 2, renderer);

	SDL_RenderPresent(renderer);
}

void Game::Clean()
{
	EnemySpawner().Clean();
	Shooting().Clean();
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	TTF_Quit();
	//Delete();
	std::cout << "Game Cleaned!" << std::endl;
}

void Game::Delete()
{
	//Objects
	delete player;
	delete background;

	//Text
	delete gameText;
	delete scoreText;
	delete healthText;
	delete baseText;

	//Other

}