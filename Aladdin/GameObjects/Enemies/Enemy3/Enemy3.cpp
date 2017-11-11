#include "Enemy3.h"

Enemy3::Enemy3()
{
	// not use
}

Enemy3::Enemy3(GameObject * player):Enemy(player)
{
	_state = new Enemy3IdleState(this);

	_attackRangeX = 150;
}


Enemy3::~Enemy3()
{
}