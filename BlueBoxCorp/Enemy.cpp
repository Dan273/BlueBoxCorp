#include "Enemy.h"
#include "Collider.h"
#include "PlayerManager.h"

Enemy::Enemy(int h, int sp, int dam, const char* text, Vector2* s, Transform* t)
{
	health = h;
	speed = sp;
	damage = dam;
	texture = text;
	scale = s;
	transform = t;
}