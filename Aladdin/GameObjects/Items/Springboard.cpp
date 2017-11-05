#include "Springboard.h"



Springboard::Springboard() : GameObject(GameObject::GameObjectType::Springboard)
{
	RECT springBoardSourceRect;
	springBoardSourceRect.left = 414;
	springBoardSourceRect.right = 457;
	springBoardSourceRect.top = 13;
	springBoardSourceRect.bottom = 31;
	_springboardSprite = new Sprite(ResourceManager::GetInstance()->GetTextureItems(), true, springBoardSourceRect);
	_width = _springboardSprite->GetWidth();
	_height = _springboardSprite->GetHeight();
}


Springboard::~Springboard()
{
	delete _springboardSprite;
}

void Springboard::Draw(Camera * camera)
{
	if (_isVisible)
	{
		_springboardSprite->SetPosition(_position);
		_springboardSprite->Draw(camera);
	}
}
