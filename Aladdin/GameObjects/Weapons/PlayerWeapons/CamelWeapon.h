#pragma once

#include "../Weapon.h"

class CamelWeapon : public Weapon
{
private:
	bool _isDelete;
public:
	CamelWeapon(int damage = 50);
	~CamelWeapon();

	void Update(float deltaTime);

	void OnCollision(GameObject *target, GameCollision::SideCollisions side);
};

