#pragma once

#include "Game.h";

class Collider
{
public:
	Collider(const Vector2* pos, const Vector2* s);

	static bool CheckCollision(Transform* A, Transform* B);

private:
	const Vector2* position;
	const Vector2* scale;
};

