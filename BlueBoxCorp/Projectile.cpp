#include "Projectile.h"

Projectile::Projectile(const char* text, int s, int d, Vector2* sc, Transform* t)
{
	texture = text;
	speed = s;
	damage = d;
	scale = sc;
	transform = t;
}