#include "Initial.h"
#include "Game.h"

Game* game = nullptr;

int main(int argc, char *argv[])
{
	Initial().StartGame();

	return 0;
}

int Initial::StartGame()
{
	if (game != nullptr)
	{
		game->Clean();
		delete game;
	}

	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	game = new Game();

	//Set the window elements
	game->init("BlueBox", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 480, 640, false);

	while (game->Running())
	{
		frameStart = SDL_GetTicks();

		game->HandleEvents();
		game->Update();
		game->Render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->Clean();

	return 0;
}

int Initial::QuitGame()
{
	game->Clean();
	return 0;
}