#include "Enemy2.h"

Enemy2::Enemy2()
{
	// not use
}

Enemy2::Enemy2(GameObject * player):Enemy(player)
{
	_state = new Enemy2IdleState(this);
}


Enemy2::~Enemy2()
{
}