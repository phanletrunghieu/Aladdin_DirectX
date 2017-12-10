#include "CamelWeapon.h"



CamelWeapon::CamelWeapon(int damage):Weapon(Weapon::WeaponType::PlayerWeapons, damage)
{
	_animation = new Animation(ResourceManager::GetInstance()->GetAnimationXMLCamelWeapon(), "fly", ResourceManager::GetInstance()->GetTextureCamel(), true, 0.5f);
	_velocity.x = 100;
}


CamelWeapon::~CamelWeapon()
{
}

void CamelWeapon::Update(float deltaTime)
{
	if (_isDelete) {
		_isVisible = false;
	}

	Weapon::Update(deltaTime);
}

void CamelWeapon::OnCollision(GameObject * target, GameCollision::SideCollisions side)
{
	if (target->GetTag() != GameObjectType::Players && target->GetTag() != GameObjectType::Camels)
	{
		_isDelete = true;
		_acceleration.y = 0;
		_velocity.x = _velocity.y = 0;
	}
}
