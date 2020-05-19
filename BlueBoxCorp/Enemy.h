#pragma once

#include "Vector2.h"
#include "Transform.h"

//This class will hold all of an enemies properties
class Enemy
{
public:
	int health;
	int speed;
	int damage;
	const char* texture;
	Vector2* scale;
	Transform* transform;

	Enemy(int h, int sp, int dam, const char* text, Vector2* s, Transform* t);
};

