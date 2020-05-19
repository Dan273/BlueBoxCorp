#pragma once

#include "Vector2.h"
#include "Transform.h"

class Projectile
{
public:
	//When we create a projectile, we need to know what the projectile texture is, what its speed is etc...
	Projectile(const char* text, int s, int d, Vector2* sc, Transform* t);

	const char* texture;
	int speed;
	int damage;
	Vector2* scale;
	Transform* transform;

private:

};

