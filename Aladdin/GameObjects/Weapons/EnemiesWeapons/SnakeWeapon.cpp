#include "SnakeWeapon.h"

SnakeWeapon::SnakeWeapon(int damage) :Weapon(Weapon::WeaponType::EnemiesWeapons, damage)
{
	_animation = new Animation(ResourceManager::GetInstance()->GetAnimationXMLJafarWeapon2(), "fire", ResourceManager::GetInstance()->GetTextureBossJafar(), true, 1.5f);

	_width = _animation->GetWidth();
	_height = _animation->GetHeight();

	_velocity.x = 40;
	_velocity.y = 0;

	_mass = 0;
	_acceleration.y = _mass;

	_allowUpdateWhenNotInCamera = true;
}

SnakeWeapon::~SnakeWeapon()
{
	delete _animation;
}

void SnakeWeapon::Draw(Camera *camera)
{
	if (_isVisible)
		_animation->Draw(camera);
}

void SnakeWeapon::Update(float deltatime)
{
	GameObject::Update(deltatime);

	_animation->SetPosition(_position);
	_animation->Update(deltatime);
	SetPosition(_animation->GetPosition());

	_width = _animation->GetWidth();
	_height = _animation->GetHeight();
}

void SnakeWeapon::OnCollision(GameObject *target, GameCollision::SideCollisions side)
{
	if (target->GetTag() != GameObject::GameObjectType::Enemies && target->GetTag() == GameObject::GameObjectType::Wall)
	{
		_isVisible = false;
		_acceleration.y = 0;
		_velocity.x = _velocity.y = 0;
	}
	
	
}