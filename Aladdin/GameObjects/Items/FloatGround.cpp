#include "FloatGround.h"



FloatGround::FloatGround() : GameObject(GameObject::GameObjectType::FloatGround)
{
	RECT floatGroundSourceRect;
	floatGroundSourceRect.left = 454;
	floatGroundSourceRect.right = 487;
	floatGroundSourceRect.top = 144;
	floatGroundSourceRect.bottom = 158;
	_floatGroundSprite = new Sprite(ResourceManager::GetInstance()->GetTextureItems(), true, floatGroundSourceRect);
	_width = _floatGroundSprite->GetWidth();
	_height = _floatGroundSprite->GetHeight();
}


FloatGround::~FloatGround()
{
	delete _floatGroundSprite;
}

void FloatGround::Draw(Camera * camera)
{
	if (_isVisible)
	{
		_floatGroundSprite->SetPosition(_position);
		_floatGroundSprite->Draw(camera);
	}
}
