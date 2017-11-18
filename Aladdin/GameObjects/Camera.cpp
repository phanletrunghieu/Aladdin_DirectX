#include "Camera.h"
#include "../GameComponents/Graphics.h"
#include "../GameComponents/Input.h"
#include "../GameComponents/SceneManager.h"

Camera* Camera::_instance = NULL;

Camera::Camera(GameObject* follow)
{
	_follow = follow;
	_width = Graphics::GetInstance()->GetScreenWidth()/2;
	_height = Graphics::GetInstance()->GetScreenHeight()/2;

	_position = D3DXVECTOR2((_width*1.0) / 2, Graphics::GetInstance()->GetScreenHeight() - (_height/2.0f));
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

	GameMap *currentMap = SceneManager::GetInstance()->GetCurrentScene()->GetGameMap();

	if (_follow != NULL)
	{
		if (_input->IsKeyPressed(DIK_LEFT) || _input->IsKeyPressed(DIK_RIGHT))
		{
			_position.x = _follow->GetPosition().x;

			//stop when at bound of map
			if (_position.x - _width / 2 < 0)
				_position.x = _width / 2;
			if (_position.x + _width / 2 > currentMap->GetWidth())
				_position.x = currentMap->GetWidth() - _width / 2;
		}

		if (_input->IsKeyPressed(DIK_UP) || _input->IsKeyPressed(DIK_DOWN))
		{
			_position.y = _follow->GetPosition().y;

			//stop when at bound of map
			if (_position.y - _height / 2 < 0)
				_position.y = _height / 2;
			if (_position.y + _height / 2 > currentMap->GetHeight())
				_position.y = currentMap->GetHeight() - _height / 2;
		}
	}
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
	D3DXVECTOR2 newPosition;
	newPosition.x = x - (_position.x - _width / 2);
	newPosition.y = y - (_position.y - _height / 2);

	//scale
	newPosition.x *= Graphics::GetInstance()->GetScreenWidth() / _width;
	newPosition.y *= Graphics::GetInstance()->GetScreenHeight() / _height;

	return newPosition;
}
