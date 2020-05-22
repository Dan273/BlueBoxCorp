#include <iostream>
#include "Shooting.h"
#include "Collider.h"
#include "EnemySpawner.h"
#include "Game.h"

std::vector<Projectile*> projectiles;
int pCount;

bool hasShot = false;

void Shooting::Shoot(Projectile* p, int c, SDL_Renderer* ren, Vector2* pos)
{
	//Spawn the projectile Transform
	Transform* newT = new Transform(p->texture, ren, pos, p->scale);

	//Spawn Projectile
	Projectile* newProj = new Projectile(NULL, p->speed, p->damage, NULL, newT);

	//Add the projectile to the list of projectiles
	projectiles.push_back(newProj);

	//Add one to the counter
	pCount++;

	//We have shot a projectile!
	std::cout << "Projectile Shot!" << std::endl;
}

bool flag = false;;
void Shooting::Update(int w, int h)
{
	if(pCount > 0)
		for (int i = 0; i < pCount; i++)
		{
			Projectile* p = projectiles.at(i);
			p->transform->position->y -= p->speed;
			//Check collision between the projectile and each enemy
			for (int e = 0; e < enemyCount; e++)
			{
				Enemy* enemy = enemies.at(e);
				//If the projectile hits and enemy, destroy the projectile and the enemy
				if (Collider::CheckCollision(p->transform, enemy->transform))
				{
					//Deduct damage from health
					enemy->health -= p->damage;

					//Destroy projectile
					projectiles.erase(projectiles.begin() + i);
					pCount--;
					p->transform->Destroy();
					delete p;

					//Destroy enemy if its health is <= 0
					if (enemy->health <= 0)
					{
						if (player != NULL)
						{

							player->score++;
							std::cout << "Score: " << player->score << std::endl;
						}
						enemies.erase(enemies.begin() + e);
						enemyCount--;
						enemy->transform->Destroy();
						delete enemy;
					}

					//We did hit an enemy
					flag = true;
					break;
				}
			}
			//If the projectile was destroyed, leave the loop
			if (flag)
			{
				flag = false;
				break;
			}
			//If the projectile hits the edge of the screen, destroy the projectile
			if (p->transform->position->y < 0 || p->transform->position->y + p->transform->scale->y > h) {
				projectiles.erase(projectiles.begin() + i);
				pCount--;
				p->transform->Destroy();
				delete p;
				break;
			}
			p->transform->Update();
		}
}

void Shooting::Render()
{
	if (pCount > 0)
		for (int i = 0; i < pCount; i++)
		{
			Projectile* p = projectiles.at(i);
			p->transform->Render();
		}
}

void Shooting::Clean()
{
	for (int i = 0; i < pCount; i++)
	{
		delete projectiles[i];
		projectiles.clear();
		pCount = 0;
	}
}