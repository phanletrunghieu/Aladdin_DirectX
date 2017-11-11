#include "Enemy1.h"



Enemy1::Enemy1()
{
	// not use
}

Enemy1::Enemy1(GameObject * player):Enemy(player)
{
	_state = new Enemy1IdleState(this);

	_prevHealth = _health;
}


Enemy1::~Enemy1()
{
}

void Enemy1::Update(float deltaTime)
{
	Enemy::Update(deltaTime);

	if (_health < _prevHealth)
	{
		SetState(new Enemy1DamageState(this));
	}
	_prevHealth = _health;
}
