#include "EnemySpawner.h"
#include <iostream>
#include "Game.h"

int enemyCount = 0;
std::vector<Enemy*> enemies;
float spawnTimer = 500;
int minSpawnTime = 80;
int spawnChange = 0;

void EnemySpawner::SpawnEnemy(Enemy* enemy, Vector2* pos, SDL_Renderer* ren)
{
	//Create the enemies Transform
	Transform* enemyT = new Transform(enemy->texture, ren, pos, enemy->scale);
	
	//Create the Enemy
	Enemy* e = new Enemy(enemy->health, enemy->speed, enemy->damage, NULL, NULL, enemyT);

	//Add the enemy GameObject to the list of enemy GameObjects
	enemies.push_back(e);

	//Increase the enemy count
	enemyCount++;

	//We spawned an enemy!
	std::cout << "Enemy Spawned!" << std::endl;
}

void EnemySpawner::SpawnEnemies(SDL_Renderer* ren, int width)
{
	if (--spawnTimer <= 0)
	{
		SpawnEnemy(enemyTypes[0], new Vector2(rand() % (width - enemyTypes[0]->scale->x) + 0, -100), ren);
		spawnTimer = minSpawnTime + (rand() % minSpawnTime*2);
		
		spawnChange++;
		//Once a certain amount of enemies spawn, the spawn time will go down, increasing difficulty
		if (minSpawnTime > 30 &&  spawnChange >= 10)
		{
			minSpawnTime -= 10;
			spawnChange = 0;
		}
	}
}

void EnemySpawner::Update(int h, SDL_Renderer* ren, int width)
{
	SpawnEnemies(ren, width);

	if(enemyCount > 0)
		for (int i = 0; i < enemyCount; i++)
		{
			Enemy* enemy = enemies.at(i);
			if (player != NULL)
			{
				//If we hit the player
				if (Collider::CheckCollision(player->transform, enemy->transform))
				{
					player->TakeDamage(enemy->damage);
					std::cout << "Player Health: " << player->health << std::endl;
					enemies.erase(enemies.begin() + i);
					enemyCount--;
					enemy->transform->Destroy();
					delete enemy;
					break;
				}
				//If we hit the bottom wall
				if (enemy->transform->position->y + enemy->transform->scale->y > h)
				{
					player->BaseDamage(enemy->damage);
					std::cout << "Base Health: " << player->baseHealth << std::endl;
					enemies.erase(enemies.begin() + i);
					enemyCount--;
					enemy->transform->Destroy();
					delete enemy;
					break;
				}
			}
			enemy->transform->position->y += enemy->speed;
			enemy->transform->Update();
		}
}

void EnemySpawner::Render()
{
	if(enemyCount > 0)
		for (int i = 0; i < enemyCount; i++)
		{
			Enemy* enemy = enemies.at(i);
			enemy->transform->Render();
		}
}

void EnemySpawner::Clean()
{
	for (int i = 0; i < enemyCount; i++)
	{
		delete enemies[i];
		enemies.clear();
		enemyCount = 0;
	}
}