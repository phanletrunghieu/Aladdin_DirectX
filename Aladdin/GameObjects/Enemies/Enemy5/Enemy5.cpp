#include "Enemy5.h"
#include "Enemy5IdleState.h"

Enemy5::Enemy5()
{
	// not use
}

Enemy5::Enemy5(GameObject * player):Enemy(player)
{
	_state = new Enemy5IdleState(this);
	_speed = 5;
}


Enemy5::~Enemy5()
{
}