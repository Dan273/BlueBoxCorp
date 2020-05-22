#pragma once

#include "Vector2.h"
#include "Enemy.h"
#include "SDL.h"
#include "Transform.h"
#include <vector>

extern int enemyCount;
extern std::vector<Enemy*> enemies;

//This class will focus on spawning enemies. Handling each enemy, and all their information
class EnemySpawner
{
public:
	//Array of enemy types
	Enemy* enemyTypes[1] = {
		new Enemy(100, 2, 25, "Assets/Sprites/Goop.png", new Vector2(64, 64), NULL)
	};

	void SpawnEnemy(Enemy* enemy, Vector2* pos, SDL_Renderer* ren);
	void SpawnEnemies(SDL_Renderer* ren, int width);

	void Update(int h, SDL_Renderer* ren, int width);
	void Render();
	void Clean();

private:

};

