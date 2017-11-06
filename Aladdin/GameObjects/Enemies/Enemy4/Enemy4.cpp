#include "Enemy4.h"

Enemy4::Enemy4()
{
	// not use
}

Enemy4::Enemy4(GameObject * player):Enemy(player)
{
	_state = new Enemy4IdleState(this);

	_attackRange = 180;
}


Enemy4::~Enemy4()
{
}