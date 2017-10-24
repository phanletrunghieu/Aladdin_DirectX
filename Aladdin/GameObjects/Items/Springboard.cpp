#include "Springboard.h"



Springboard::Springboard() : GameObject(GameObject::GameObjectType::Springboard)
{
	_springboardSprite = new Sprite(L"Resources/Items/springboard.png");
	_width = _springboardSprite->GetWidth();
	_height = _springboardSprite->GetHeight();
}


Springboard::~Springboard()
{
}

void Springboard::Draw(Camera * camera)
{
	if (_isVisible)
	{
		_springboardSprite->SetPosition(_position);
		_springboardSprite->Draw(camera);
	}
}
