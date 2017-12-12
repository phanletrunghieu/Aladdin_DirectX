#include "JafarWeapon.h"

JafarWeapon::JafarWeapon(int damage) :Weapon(Weapon::WeaponType::EnemiesWeapons, damage)
{
	_animationFly = new Animation(ResourceManager::GetInstance()->GetAnimationXMLJafarWeapon1(), "fly", ResourceManager::GetInstance()->GetTextureBossJafar(), true, 3.0f);
	_animationExploide = new Animation(ResourceManager::GetInstance()->GetAnimationXMLJafarWeapon1(), "explode", ResourceManager::GetInstance()->GetTextureBossJafar(), true, 3.0f);
	
	_animation = _animationFly;

	_width = _animation->GetWidth();
	_height = _animation->GetHeight();

	_velocity.x = 1;
	_velocity.y = 1;

	_mass = 0;
	_acceleration.y = _mass;

	_allowUpdateWhenNotInCamera = true;
}

JafarWeapon::~JafarWeapon()
{
	if (_animationFly && _animation != _animationFly)
	{
		delete _animationFly;
		_animationFly = 0;
	}

	if (_animationFly && _animation != _animationExploide)
	{
		delete _animationExploide;
		_animationExploide = 0;
	}
}

void JafarWeapon::Draw(Camera* camera)
{
	if (_isVisible)
		_animation->Draw(camera);
}

void JafarWeapon::Update(float deltatime)
{
	Weapon::Update(deltatime);

	if (_animation->IsFinish() && _animation == _animationExploide)
	{
		_isVisible = false;
	}
}

void JafarWeapon::OnCollision(GameObject* target, GameCollision::SideCollisions side)
{
	if (target->GetTag() != GameObject::GameObjectType::Enemies && target->GetTag() != GameObject::GameObjectType::Weapons && _animation!= _animationExploide)
	{
		_animation = _animationExploide;
		_width = _animation->GetWidth();
		_height = _animation->GetHeight();

		_acceleration.y = 0;
		_velocity.x = _velocity.y = 0;
	}
}