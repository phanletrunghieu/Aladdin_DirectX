#pragma once

#include "../Weapon.h"

class Enemy6Weapon : public Weapon
{
private:
	Animation *_animationFall;
	Animation *_animationExplode;
public:
	Enemy6Weapon(int damage = 10);
	~Enemy6Weapon();

	void Update(float deltaTime);

	void OnCollision(GameObject *target, GameCollision::SideCollisions side);
};

