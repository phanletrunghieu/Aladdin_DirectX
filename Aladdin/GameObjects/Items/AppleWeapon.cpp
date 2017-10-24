#include "AppleWeapon.h"

AppleWeapon::AppleWeapon():GameObject(GameObject::GameObjectType::AppleWeapon)
{
	_animationFly = new Animation(ResourceManager::GetInstance()->GetAppleWeaponAnimationXML(), "Fly", ResourceManager::GetInstance()->GetAladdinTexture(), 0.5f);
	_animationExplode = new Animation(ResourceManager::GetInstance()->GetAppleWeaponAnimationXML(), "Explode", ResourceManager::GetInstance()->GetAladdinTexture(), 0.4f);

	_currentAnimation = _animationFly;
	_width = _currentAnimation->GetWidth();
	_height = _currentAnimation->GetHeight();

	_velocity.x = 30;//left or right
	_velocity.y = -20;

	_mass = 10;
	_acceleration.y = _mass;
}


AppleWeapon::~AppleWeapon()
{
}

void AppleWeapon::Draw(Camera * camera)
{
	if (_isVisible)
		_currentAnimation->Draw(camera);
}

void AppleWeapon::Update(float deltaTime)
{
	GameObject::Update(deltaTime);

	_currentAnimation->Update(deltaTime);
	_currentAnimation->SetPosition(_position);

	if (_currentAnimation->IsFinish() && _currentAnimation == _animationExplode) {
		_isVisible = false;
	}
}

void AppleWeapon::OnCollision(GameObject * target, GameCollision::SideCollisions side)
{
	if (target->GetTag() != GameObjectType::Player)
	{
		_currentAnimation = _animationExplode;
		_width = _currentAnimation->GetWidth();
		_height = _currentAnimation->GetHeight();

		_acceleration.y = 0;
		_velocity.x = _velocity.y = 0;
	}
}
