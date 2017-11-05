#include "Enemy3Weapon.h"



Enemy3Weapon::Enemy3Weapon(int damage) : Weapon(Weapon::WeaponType::EnemiesWeapons, damage)
{
	_animation = new Animation(ResourceManager::GetInstance()->GetAnimationXMLEnemy3Weapon(), "Rotate", ResourceManager::GetInstance()->GetTextureItems(), true, 0.5f);

	_width = _animation->GetWidth();
	_height = _animation->GetHeight();

	_velocity.x = 50;//left or right
	_velocity.y = -20;

	_mass = 10;
	_acceleration.y = _mass;
}

Enemy3Weapon::~Enemy3Weapon()
{
	delete _animation;
}

void Enemy3Weapon::Draw(Camera * camera)
{
	if (_isVisible)
		_animation->Draw(camera);
}

void Enemy3Weapon::Update(float deltaTime)
{
	GameObject::Update(deltaTime);

	_animation->SetPosition(_position);
	_animation->Update(deltaTime);
	SetPosition(_animation->GetPosition());

	_width = _animation->GetWidth();
	_height = _animation->GetHeight();
}

void Enemy3Weapon::OnCollision(GameObject * target, GameCollision::SideCollisions side)
{
	if (target->GetTag() != GameObject::GameObjectType::Enemies)
	{
		_isVisible = false;
		_acceleration.y = 0;
		_velocity.x = _velocity.y = 0;
	}
}
