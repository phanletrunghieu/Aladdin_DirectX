#pragma once

#include "../Weapon.h"

class AppleWeapon : public Weapon
{
private:
	Animation *_animationFly, *_animationExplode;
public:
	AppleWeapon(int damage = 50);
	~AppleWeapon();

	void Update(float deltaTime);

	void OnCollision(GameObject *target, GameCollision::SideCollisions side);
};

