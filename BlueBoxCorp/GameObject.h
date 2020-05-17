#pragma once

#include "Game.h"

class GameObject
{
public:
	GameObject(const char* n, Transform* t, bool gravity);
	~GameObject();

	Transform* transform;

private:
	const char* name;
	bool useGravity;
};

