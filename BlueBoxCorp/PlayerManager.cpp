#include "PlayerManager.h"

PlayerManager::PlayerManager(Transform* t, int bH, int h, int sh, int s, int hS)
{
	transform = t;
	baseHealth = bH;
	health = h;
	shield = sh;
	score = s;
	highScore = hS;
}

void PlayerManager::TakeDamage(int dam)
{
	//We need to check if the player has a shield
	if (shield > 0)
	{
		//If the player has a shield, then deduct the damage done from that first
		if (shield >= dam)
		{
			shield -= dam;
		}
		else //If there isnt enough shield, then we need to take the remainder off the health
		{
			//Take it off of the shield to give the remainder
			shield -= dam;
			//Take the remainder off of the health
			health += shield;
			//Set the shield back to 0
			shield = 0;
		}
	}
	else //If we dont have a shield, just take it off of the health
	{
		health -= dam;
	}
}

void PlayerManager::BaseDamage(int dam)
{
	//Deduct health off of the base
	baseHealth -= dam;
}