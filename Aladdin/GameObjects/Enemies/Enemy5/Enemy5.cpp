#include "Enemy5.h"

Enemy5::Enemy5()
{
	// not use
}

Enemy5::Enemy5(GameObject * player):Enemy(player)
{
	_speed = 5;

	_state = new Enemy5IdleState(this);
}


Enemy5::~Enemy5()
{
}