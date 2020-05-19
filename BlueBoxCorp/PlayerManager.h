#pragma once

#include "Transform.h"

class PlayerManager
{
public:
	Transform* transform;

	int baseHealth = 250;
	int health = 100;
	int shield = 0;

	int score = 0;
	int highScore = 0;

	PlayerManager(Transform* t, int bH, int h, int sh, int s, int hS);

	void TakeDamage(int dam);
	void BaseDamage(int dam);

};

