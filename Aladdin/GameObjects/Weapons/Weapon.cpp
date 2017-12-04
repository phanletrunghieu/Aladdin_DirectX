#include "Weapon.h"

Weapon::Weapon():GameObject(GameObject::GameObjectType::Weapons, true)
{
}

Weapon::Weapon(Weapon::WeaponType weaponType, int damage) : GameObject(GameObject::GameObjectType::Weapons)
{
	_weaponType = weaponType;
	_damage = damage;
	_isAttacked = false;
}


Weapon::~Weapon()
{
}

void Weapon::Draw(Camera * camera)
{
	if (_isVisible && _animation!=NULL)
		_animation->Draw(camera);
}

void Weapon::Update(float deltaTime)
{
	GameObject::Update(deltaTime);

	if (!_isInCamera)
		return;

	if (_animation)
	{
		_animation->SetPosition(_position);
		_animation->Update(deltaTime);
		SetPosition(_animation->GetPosition());

		_width = _animation->GetWidth();
		_height = _animation->GetHeight();
	}
}

int Weapon::GetDamage()
{
	return _damage;
}

void Weapon::SetDamage(int value)
{
	_damage = value;
}

Animation * Weapon::GetAnimation()
{
	return _animation;
}

Weapon::WeaponType Weapon::GetWeaponType()
{
	return _weaponType;
}

bool Weapon::IsAttacked()
{
	return _isAttacked;
}

void Weapon::SetIsAttacked(bool value)
{
	_isAttacked = value;
}
