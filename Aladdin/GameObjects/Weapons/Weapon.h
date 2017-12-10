#pragma once

#include "../GameObject.h"
#include "../../GameComponents/Animation.h"

class Weapon : public GameObject
{
public:
	enum WeaponType
	{
		PlayerWeapons, EnemiesWeapons
	};

	Weapon();
	Weapon(Weapon::WeaponType weaponType, int damage = 10);
	virtual ~Weapon();

	void Draw(Camera* camera);
	void Update(float deltaTime);

	int GetDamage();
	void SetDamage(int value);

	Animation* GetAnimation();

	Weapon::WeaponType GetWeaponType();

	bool IsAttacked();
	void SetIsAttacked(bool value);
protected:
	WeaponType _weaponType;

	int _damage;
	Animation *_animation;

	//used to make sure that target is attacked once at each collision
	bool _isAttacked;
};

