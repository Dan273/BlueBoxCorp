#include "GameObject.h"

GameObject::GameObject(const char* n, Transform* t, bool gravity)
{
	name = n;
	transform = t;
	useGravity = gravity;
}