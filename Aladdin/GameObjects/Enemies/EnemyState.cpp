#include "EnemyState.h"
#include "Enemy.h"


EnemyState::EnemyState()
{
}

EnemyState::EnemyState(Enemy * enemy, StateName name)
{
	_name = name;
	_enemy = enemy;
}


EnemyState::~EnemyState()
{
	delete _animation;
}

void EnemyState::Update(float deltaTime)
{
	if (_animation != NULL)
	{
		_animation->SetPosition(_enemy->GetPosition());
		_animation->FlipHorizontal(_enemy->IsRight());

		_animation->Update(deltaTime);//after animation update, animation's position maybe change
		_enemy->SetPosition(_animation->GetPosition());
	}

	_enemy->SetWidth(_animation->GetWidth());
	_enemy->SetHeight(_animation->GetHeight());
}

Animation * EnemyState::GetAnimation()
{
	return _animation;
}

EnemyState::StateName EnemyState::GetName()
{
	return _name;
}
