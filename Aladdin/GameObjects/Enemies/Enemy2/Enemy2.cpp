#include "Enemy2.h"

Enemy2::Enemy2()
{
	// not use
}

Enemy2::Enemy2(GameObject * player):Enemy(player)
{
	_state = new Enemy2IdleState(this);

	_prevHealth = _health;
}


Enemy2::~Enemy2()
{
}

void Enemy2::Update(float deltaTime)
{
	Enemy::Update(deltaTime);

	if (_health < _prevHealth)
	{
		SetState(new Enemy2Damage1State(this));
	}
	_prevHealth = _health;
}
