#include "Apple.h"

Apple::Apple():GameObject(GameObject::GameObjectType::Apple)
{
	_appleSprite = new Sprite(L"Resources/Items/apple.png");
	_width = _appleSprite->GetWidth();
	_height = _appleSprite->GetHeight();
}


Apple::~Apple()
{
}

void Apple::Draw(Camera * camera)
{
	if (_isVisible)
	{
		_appleSprite->SetPosition(_position);
		_appleSprite->Draw(camera);
	}
}

void Apple::OnCollision(GameObject * target, GameCollision::SideCollisions side)
{
	if (target->GetTag() == GameObjectType::Player)
	{
		_isVisible = false;
	}
}
