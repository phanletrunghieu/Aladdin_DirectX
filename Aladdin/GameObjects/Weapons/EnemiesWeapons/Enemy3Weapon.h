#pragma once

#include "../Weapon.h"

class Enemy3Weapon : public Weapon
{
public:
	Enemy3Weapon(int damage = 10);
	~Enemy3Weapon();

	void OnCollision(GameObject *target, GameCollision::SideCollisions side);
};

