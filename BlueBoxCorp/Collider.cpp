#include "Collider.h"

Collider::Collider(const Vector2* pos, const Vector2* s)
{
	position = pos;
	scale = s;
}

bool Collider::CheckCollision(Transform* A, Transform* B)
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = A->position->x;
    rightA = A->position->x + A->scale->x;
    topA = A->position->y;
    bottomA = A->position->y + A->scale->y;

    //Calculate the sides of rect B
    leftB = B->position->x;
    rightB = B->position->x + B->scale->x;
    topB = B->position->y;
    bottomB = B->position->y + B->scale->y;

    //If any of the sides from A are outside of B
    if (bottomA <= topB)
    {
        return false;
    }

    if (topA >= bottomB)
    {
        return false;
    }

    if (rightA <= leftB)
    {
        return false;
    }

    if (leftA >= rightB)
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}