#pragma once

#include "../GameObject.h"

class Weapon : public GameObject
{
public:
	enum WeaponType
	{
		PlayerWeapons, EnemiesWeapons
	};

	Weapon();
	Weapon(Weapon::WeaponType weaponType, int damage = 10);
	~Weapon();

	int GetDamage();
	void SetDamage(int value);

	Weapon::WeaponType GetWeaponType();
protected:
	WeaponType _weaponType;

	int _damage;
};

