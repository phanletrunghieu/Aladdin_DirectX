#include "FloatGround.h"



FloatGround::FloatGround() : GameObject(GameObject::GameObjectType::FloatGround)
{
	_floatGroundSprite = new Sprite(L"Resources/Items/FloatGround.png");
	_width = _floatGroundSprite->GetWidth();
	_height = _floatGroundSprite->GetHeight();
}


FloatGround::~FloatGround()
{
}

void FloatGround::Draw(Camera * camera)
{
	if (_isVisible)
	{
		_floatGroundSprite->SetPosition(_position);
		_floatGroundSprite->Draw(camera);
	}
}
