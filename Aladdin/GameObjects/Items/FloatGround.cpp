#include "FloatGround.h"



FloatGround::FloatGround() : GameObject(GameObject::GameObjectType::FloatGround, true)
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

void FloatGround::OnCollision(GameObject * target, GameCollision::SideCollisions side)
{
	if (target->GetTag() == GameObject::GameObjectType::Players)
	{
		_velocity.y = 0;
		_acceleration.y = 60;
	}

	if (target->GetTag() == GameObject::GameObjectType::Ground)
	{
		_acceleration.y = 0;
		_velocity.y = 0;
		_position = _firstPosition;
	}
}

void FloatGround::SetPosition(D3DXVECTOR2 position)
{
	GameObject::SetPosition(position);
	_firstPosition = position;
}

void FloatGround::SetPosition(D3DXVECTOR3 position)
{
	GameObject::SetPosition(position);
	_firstPosition = D3DXVECTOR2(position);
}

void FloatGround::SetPosition(float x, float y)
{
	GameObject::SetPosition(x, y);
	_firstPosition = D3DXVECTOR2(x, y);
}
