#include "EnemyState.h"
#include "Enemy.h"


EnemyState::EnemyState()
{
}

EnemyState::EnemyState(Enemy * enemy, StateName name)
{
	_name = name;
	_enemy = enemy;

	_totalDuration = 0;

	//special for attack state
	_isAttackedPlayer = false;
}


EnemyState::~EnemyState()
{
	delete _animation;
}

void EnemyState::Update(float deltaTime)
{
	_totalDuration += deltaTime;

	if (_animation != NULL)
	{
		_animation->SetPosition(_enemy->GetPosition());

		if (_animation->IsSourceRight())
		{
			if(_enemy->IsAllowMoveLeft())
				_animation->FlipHorizontal(!_enemy->IsRight());
		}
		else
		{
			if (_enemy->IsAllowMoveRight())
				_animation->FlipHorizontal(_enemy->IsRight());
		}

		_animation->Update(deltaTime);//after animation update, animation's position maybe change
		_enemy->SetPosition(_animation->GetPosition());
	}

	_enemy->SetWidth(_animation->GetWidth());
	_enemy->SetHeight(_animation->GetHeight());

	//reset "_isAttackedPlayer"
	if (_animation->IsBegin())
		_isAttackedPlayer = false;
}

Animation * EnemyState::GetAnimation()
{
	return _animation;
}

void EnemyState::SetAnimation(Animation * newAnimation)
{
	_animation = newAnimation;

	if (_animation->IsSourceRight())
		_animation->FlipHorizontal(!_enemy->IsRight());
	else
		_animation->FlipHorizontal(_enemy->IsRight());

	_animation->SetPosition(_enemy->GetPosition());
	_enemy->SetWidth(_animation->GetWidth());
	_enemy->SetHeight(_animation->GetHeight());
}

EnemyState::StateName EnemyState::GetName()
{
	return _name;
}

bool EnemyState::IsAttackedPlayer()
{
	return _isAttackedPlayer;
}

void EnemyState::SetIsAttackedPlayer(bool value)
{
	_isAttackedPlayer = value;
}
