#include "Enemy.h"


Enemy::Enemy() : GameObject(GameObject::GameObjectType::Enemy)
{
	_health = 0;
	_isRight = false;
	UpdateViewRange();
}

Enemy::~Enemy()
{
	delete _state;
}

void Enemy::Update(float deltaTime)
{
	GameObject::Update(deltaTime);
	UpdateViewRange();


}

void Enemy::Draw(Camera * camera)
{
	_state->GetAnimation()->Draw(camera);
}

void Enemy::OnCollision(GameObject * target, GameCollision::SideCollisions side)
{
	_state->OnCollision(target, side);
}

EnemyState * Enemy::GetState()
{
	return _state;
}

void Enemy::SetState(EnemyState * state, bool fixFootPosition)
{
	if (fixFootPosition)
	{
		//make sure enemy's foot at the same position when change state. because each state has own height
		int newHeight = state->GetAnimation()->GetHeight();
		int currentHeight = _state->GetAnimation()->GetHeight();
		float diff = (currentHeight - newHeight) / 2.0;
		_position.y += diff;
	}

	//change state
	delete _state;
	_state = state;
}

void Enemy::UpdateViewRange()
{
	if (_isRight)
	{
		_viewRange.left = _position.x;
		_viewRange.right = _viewRange.left + 10;
		_viewRange.top = _position.y - _height / 2;
		_viewRange.bottom = _viewRange.top + _height;
	}
	else
	{
		_viewRange.right = _position.x;
		_viewRange.left = _viewRange.right - 10;
		_viewRange.top = _position.y - _height / 2;
		_viewRange.bottom = _viewRange.top + _height;
	}
}

int Enemy::GetHealth()
{
	return _health;
}

void Enemy::SetHealth(int newHealth)
{
	_health = newHealth;
}

void Enemy::SetPosition(float x, float y)
{
	GameObject::SetPosition(x, y);
	UpdateViewRange();
}

void Enemy::SetPosition(D3DXVECTOR2 position)
{
	GameObject::SetPosition(position);
	UpdateViewRange();
}

void Enemy::SetPosition(D3DXVECTOR3 position)
{
	GameObject::SetPosition(position);
	UpdateViewRange();
}

void Enemy::SetPositionX(float x)
{
	GameObject::SetPositionX(x);
	UpdateViewRange();
}

void Enemy::SetPositionY(float y)
{
	GameObject::SetPositionY(y);
	UpdateViewRange();
}

bool Enemy::IsRight()
{
	return _isRight;
}
