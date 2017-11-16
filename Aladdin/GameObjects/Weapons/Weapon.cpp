#include "Weapon.h"

Weapon::Weapon():GameObject(GameObject::GameObjectType::Weapons, true)
{
}

Weapon::Weapon(Weapon::WeaponType weaponType, int damage) : GameObject(GameObject::GameObjectType::Weapons)
{
	_weaponType = weaponType;
	_damage = damage;
}


Weapon::~Weapon()
{
}

int Weapon::GetDamage()
{
	return _damage;
}

void Weapon::SetDamage(int value)
{
	_damage = value;
}

Weapon::WeaponType Weapon::GetWeaponType()
{
	return _weaponType;
}
