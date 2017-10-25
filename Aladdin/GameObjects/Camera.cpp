#include "Camera.h"

Camera* Camera::_instance = NULL;

Camera::Camera(GameObject* follow)
{
	_follow = follow;
	_width = Graphics::GetInstance()->GetScreenWidth();
	_height = Graphics::GetInstance()->GetScreenHeight();

	_position = D3DXVECTOR2((_width*1.0) / 2, (_height*1.0) / 2);
	_position.x = _follow->GetPosition().x;

	this->_instance = this;
}

Camera::~Camera()
{
}

Camera * Camera::GetInstance()
{
	if (!_instance)
		_instance = new Camera();

	return _instance;
}

void Camera::Update(float deltaTime)
{
	GameObject::Update(deltaTime);

	if (_follow != NULL && (_input->IsKeyPressed(DIK_LEFT) || _input->IsKeyPressed(DIK_RIGHT)))
	{
		_position.x = _follow->GetPosition().x;
	}
	/*
	if (Input::GetInstance()->IsKeyPressed(DIK_RIGHT))
		_position.x += 0.1f;

	if (Input::GetInstance()->IsKeyPressed(DIK_LEFT))
		_position.x -= 0.1f;

	if (Input::GetInstance()->IsKeyPressed(DIK_UP))
		_position.y -= 0.1f;

	if (Input::GetInstance()->IsKeyPressed(DIK_DOWN))
		_position.y += 0.1f;
	*/
}

bool Camera::IsInCamera(D3DXVECTOR2 position, int width, int height)
{
	float _left, _right, _top, _bottom;
	GetBound(_top, _right, _bottom, _left);

	float left = position.x - ((float)width) / 2;
	float right = position.x + ((float)width) / 2;
	float top = position.y - ((float)height) / 2;
	float bottom = position.y + ((float)height) / 2;

	if (_left > right || _right<left || _top>bottom || _bottom < top)
		return false;
	return true;
}

D3DXVECTOR2 Camera::ConvertPosition(D3DXVECTOR2 position)
{
	return ConvertPosition(position.x, position.y);
}

D3DXVECTOR2 Camera::ConvertPosition(float x, float y)
{
	float screenWidth = Graphics::GetInstance()->GetScreenWidth()*1.0;
	float screenHeight = Graphics::GetInstance()->GetScreenHeight()*1.0;

	D3DXVECTOR2 newPosition;
	newPosition.x = x - (_position.x - screenWidth / 2);
	newPosition.y = y - (_position.y - screenHeight / 2);
	return newPosition;
}
