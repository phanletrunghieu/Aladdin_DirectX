#include "Enemy.h"

Enemy::Enemy() : GameObject(GameObject::GameObjectType::Enemy)
{
	//not use
}

Enemy::Enemy(GameObject * target) : GameObject(GameObject::GameObjectType::Enemy)
{
	_target = target;
	_distanceToTarget = _target->GetPosition() - _position;

	_footPosY = 0;

	_health = 0;
	_speed = 10;
	_viewRange = 300;
	_attackRange = 80;
	_isRight = false;
}

Enemy::~Enemy()
{
	delete _state;
}

void Enemy::Update(float deltaTime)
{
	/*handle move action here*/
	_distanceToTarget = _target->GetPosition() - _position;

	//face to left or right
	if(_distanceToTarget.x > 0)
		_isRight = true;
	else if (_distanceToTarget.x < 0)
		_isRight = false;

	//move
	if(IsTargetInViewRange() && !IsTargetInAttackRange())
	{
		if (_distanceToTarget.x > 0)
		{
			//move right
			_velocity.x = _speed;
		}
		else if(_distanceToTarget.x < 0)
		{
			//move left
			_velocity.x = -1 * _speed;
		}
	}
	else
	{
		//v=0
		_velocity.x = 0;
	}

	GameObject::Update(deltaTime);
	_state->Update(deltaTime);

	//fix foot posY
	_position.y = _footPosY - _height / 2;
}

void Enemy::Draw(Camera * camera)
{
	Animation *animation = _state->GetAnimation();
	if (animation != NULL)
		animation->Draw(camera);
}

void Enemy::OnCollision(GameObject * target, GameCollision::SideCollisions side)
{
	_state->OnCollision(target, side);
}

bool Enemy::IsTargetInViewRange()
{
	if (abs(_distanceToTarget.x) <= _viewRange && abs(_distanceToTarget.y) < _height)
		return true;
	return false;
}

bool Enemy::IsTargetInAttackRange()
{
	if (abs(_distanceToTarget.x) <= _attackRange && abs(_distanceToTarget.y) < _height)
		return true;
	return false;
}

void Enemy::SetFootPosY()
{
	if (_footPosY == 0)
		_footPosY = _position.y + _height / 2;
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

GameObject * Enemy::GetTarget()
{
	return _target;
}

int Enemy::GetHealth()
{
	return _health;
}

void Enemy::SetHealth(int newHealth)
{
	_health = newHealth;
}

bool Enemy::IsRight()
{
	return _isRight;
}

void Enemy::SetIsRight(bool right)
{
	_isRight = right;
}

void Enemy::SetPosition(float x, float y)
{
	GameObject::SetPosition(x, y);
	SetFootPosY();
}

void Enemy::SetPosition(D3DXVECTOR2 position)
{
	GameObject::SetPosition(position);
	SetFootPosY();
}

void Enemy::SetPosition(D3DXVECTOR3 position)
{
	GameObject::SetPosition(position);
	SetFootPosY();
}
