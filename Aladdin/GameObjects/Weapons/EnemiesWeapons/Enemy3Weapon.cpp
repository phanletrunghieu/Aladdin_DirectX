#include "Enemy3Weapon.h"



Enemy3Weapon::Enemy3Weapon(int damage) : Weapon(Weapon::WeaponType::EnemiesWeapons, damage)
{
	_animation = new Animation(ResourceManager::GetInstance()->GetAnimationXMLEnemy3Weapon(), "Rotate", ResourceManager::GetInstance()->GetTextureEnemies1(), true, 0.3f);

	_width = _animation->GetWidth();
	_height = _animation->GetHeight();

	_velocity.x = 35;//left or right
	_velocity.y = -20;

	_mass = 10;
	_acceleration.y = _mass;
}

Enemy3Weapon::~Enemy3Weapon()
{
	delete _animation;
}

void Enemy3Weapon::OnCollision(GameObject * target, GameCollision::SideCollisions side)
{
	//prevent collision with PlayerWeapons
	if (target->GetTag() == GameObjectType::Weapons)
	{
		Weapon* weapon = dynamic_cast<Weapon*>(target);
		if (weapon->GetWeaponType() == Weapon::WeaponType::PlayerWeapons)
			return;
	}

	if (target->GetTag() != GameObject::GameObjectType::Enemies
		&& target->GetTag() != GameObject::GameObjectType::Apple)
	{
		_isVisible = false;
		_acceleration.y = 0;
		_velocity.x = _velocity.y = 0;
	}
}
