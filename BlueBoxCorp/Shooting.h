#pragma once

#include "SDL.h"
#include "Projectile.h"
#include "Vector2.h"
#include "Transform.h"
#include <vector>

extern bool hasShot;

class Shooting
{
public:
	//We will have a predefined list of projectiles so that they can be easily set in game
	Projectile* projectileTypes[2] = {
			new Projectile("Assets/Sprites/Laser.png", 2, 100, new Vector2(4, 8), NULL), 
			new Projectile("Assets/Sprites/Laser/Rocket.png", 5, 100, new Vector2(8, 16), NULL)

	};

	//The shoot class will be used to fire a new projectile
	void Shoot(Projectile* p, int c, SDL_Renderer* ren, Vector2* pos);
	void Update(int w, int h);
	void Render();

private:

};