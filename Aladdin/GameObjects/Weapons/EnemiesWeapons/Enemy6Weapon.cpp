#include "Enemy6Weapon.h"



Enemy6Weapon::Enemy6Weapon(int damage) : Weapon(Weapon::WeaponType::EnemiesWeapons, damage)
{
	_animationFall = new Animation(ResourceManager::GetInstance()->GetAnimationXMLEnemy6Weapon(), "fall", ResourceManager::GetInstance()->GetTextureEnemies2(), true, 0.3f);
	_animationExplode = new Animation(ResourceManager::GetInstance()->GetAnimationXMLEnemy6Weapon(), "explode", ResourceManager::GetInstance()->GetTextureEnemies2(), true, 0.3f);
	_animation = _animationFall;

	_width = _animation->GetWidth();
	_height = _animation->GetHeight();

	_mass = 10;
	_acceleration.y = _mass;
}

Enemy6Weapon::~Enemy6Weapon()
{
	delete _animation;
}

void Enemy6Weapon::Update(float deltaTime)
{
	Weapon::Update(deltaTime);

	if (_animation->IsFinish() && _animation == _animationExplode)
	{
		_isVisible = false;
	}
}

void Enemy6Weapon::OnCollision(GameObject * target, GameCollision::SideCollisions side)
{
	if (target->GetTag() != GameObject::GameObjectType::Enemies)
	{
		_animation = _animationExplode;
		_width = _animation->GetWidth();
		_height = _animation->GetHeight();

		_acceleration.y = 0;
		_velocity.x = _velocity.y = 0;
	}
}
