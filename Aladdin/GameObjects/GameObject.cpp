#include "GameObject.h"
#include "Camera.h"
#include "../GameComponents/SceneManager.h"

GameObject::GameObject(GameObjectType tag, bool isMovableObject)
{
	_tag = tag;
	_isMovableObject = isMovableObject;

	_mass = 0;

	_position = D3DXVECTOR2(0, 0);
	_prevPosition = D3DXVECTOR2(-1, -1);
	_velocity = D3DXVECTOR2(0, 0);
	_acceleration = D3DXVECTOR2(0, _mass);

	_isVisible = true;
	_allowUpdateWhenNotInCamera = false;

	_input = Input::GetInstance();

	_noCheckCollision.push_back(GameObjectType::Ground);
	_noCheckCollision.push_back(GameObjectType::Colbany);
	_noCheckCollision.push_back(GameObjectType::Camels);
	_noCheckCollision.push_back(GameObjectType::HorizontalBar);
	_noCheckCollision.push_back(GameObjectType::None);
	_noCheckCollision.push_back(GameObjectType::Rope);
	_noCheckCollision.push_back(GameObjectType::Springboard);
	_noCheckCollision.push_back(GameObjectType::ScoreObjects);
}


GameObject::~GameObject()
{
}

void GameObject::Update(float deltaTime)
{
	if (_camera == NULL)
		_camera = SceneManager::GetInstance()->GetCurrentScene()->GetCamera();
	_isInCamera = _camera->IsInCamera(_position, _width, _height);

	if (!_isInCamera && !_allowUpdateWhenNotInCamera)
		return;

	_deltaTime = deltaTime;

	//delta(v)=a*delta(t)
	_velocity += _acceleration*deltaTime;

	//s=v*delta(t)
	_position += _velocity*deltaTime;

	//collision
	bool isCheckCollision = true;
	for (size_t i = 0; i < _noCheckCollision.size(); i++)
	{
		if (_tag == _noCheckCollision.at(i)) {
			isCheckCollision = false;
			break;
		}
	}

	if (_isInCamera && isCheckCollision)
		this->CheckCollision();

	//fixed position
	if (_prevPosition.x == -1 && _prevPosition.x == -1) {//not yet init
		_prevPosition = _position;
	}
	if (!_isMovableObject) {
		_position = _prevPosition;
	}
}

void GameObject::CheckCollision()
{
	std::vector<GameObject*> listCanCollide;
	SceneManager::GetInstance()->GetCurrentScene()->GetQuadTree()->Retrieve(listCanCollide, this);
	for (size_t i = 0; i < listCanCollide.size(); i++)
	{
		GameObject *gameObject = listCanCollide.at(i);
		bool isInCamera = _camera->IsInCamera(gameObject->GetPosition(), gameObject->GetWidth(), gameObject->GetHeight());
		if (!gameObject->IsVisible() || !isInCamera)
			continue;
		//khong cho player xet va cham voi weapon
		if (this->_tag == GameObjectType::Players && gameObject->_tag == GameObjectType::Weapons)
			continue;

		//lay va cham cua other voi this
		GameCollision collisionData = GameCollision::CheckCollision(this->GetBound(), gameObject->GetBound());
		if (collisionData.IsCollided()) {
			this->OnCollision(gameObject, collisionData.GetSide());

			//goi va cham cho player voi weapon
			if (this->_tag == GameObjectType::Weapons && gameObject->_tag == GameObjectType::Players)
				gameObject->OnCollision(this, collisionData.GetSide());
		}
	}
}

GameObject::GameObjectType GameObject::GetTag()
{
	return _tag;
}

bool GameObject::IsVisible()
{
	return _isVisible;
}

void GameObject::SetIsVisible(bool value)
{
	_isVisible = value;
}

bool GameObject::IsMovableObject()
{
	return _isMovableObject;
}

D3DXVECTOR2 GameObject::GetPosition()
{
	return _position;
}

void GameObject::SetPosition(float x, float y)
{
	_position.x = x;
	_position.y = y;
}

void GameObject::SetPosition(D3DXVECTOR2 position)
{
	_position = position;
}

void GameObject::SetPosition(D3DXVECTOR3 position)
{
	_position.x = position.x;
	_position.y = position.y;
}

void GameObject::SetPositionX(float x)
{
	_position.x = x;
}

void GameObject::SetPositionY(float y)
{
	_position.y = y;
}

D3DXVECTOR2 GameObject::GetVelocity()
{
	return _velocity;
}

void GameObject::SetVelocity(float x, float y)
{
	_velocity.x = x;
	_velocity.y = y;
}

void GameObject::SetVelocity(D3DXVECTOR2 velociy)
{
	_velocity = velociy;
}

void GameObject::SetVelocityX(float x)
{
	_velocity.x = x;
}

void GameObject::SetVelocityY(float y)
{
	_velocity.y = y;
}

D3DXVECTOR2 GameObject::GetAcceleration()
{
	return _acceleration;
}

void GameObject::SetAcceleration(float x, float y)
{
	_acceleration.x = x;
	_acceleration.y = y;
}

void GameObject::SetAccelerationX(float x)
{
	_acceleration.x = x;
}

void GameObject::SetAccelerationY(float y)
{
	_acceleration.y = y;
}

float GameObject::GetMass()
{
	return _mass;
}

void GameObject::SetMass(float mass)
{
	_mass = mass;
}

int GameObject::GetWidth()
{
	return _width;
}

void GameObject::SetWidth(int width)
{
	_width = width;
}

int GameObject::GetHeight()
{
	return _height;
}

void GameObject::SetHeight(int height)
{
	_height = height;
}

void GameObject::GetBound(float & top, float & right, float & bottom, float & left)
{
	top = _position.y - ((float)_height) / 2;
	right = _position.x + ((float)_width) / 2;
	bottom = _position.y + ((float)_height) / 2;
	left = _position.x - ((float)_width) / 2;
}

RECT GameObject::GetBound()
{
	RECT bound;
	bound.top = _position.y - ((float)_height) / 2;
	bound.right = _position.x + ((float)_width) / 2;
	bound.bottom = _position.y + ((float)_height) / 2;
	bound.left = _position.x - ((float)_width) / 2;
	return bound;
}
