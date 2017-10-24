#include "Apple.h"

Apple::Apple():GameObject(GameObject::GameObjectType::Apple)
{
	RECT appleSourceRect;
	appleSourceRect.left = 341;
	appleSourceRect.right = 352;
	appleSourceRect.top = 17;
	appleSourceRect.bottom = 29;

	_appleSprite = new Sprite(ResourceManager::GetInstance()->GetTextureItems(), appleSourceRect);
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
