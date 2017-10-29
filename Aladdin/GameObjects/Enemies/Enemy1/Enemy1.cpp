#include "Enemy1.h"



Enemy1::Enemy1()
{
	// not use
}

Enemy1::Enemy1(GameObject * player):Enemy(player)
{
	_state = new Enemy1IdleState(this);
}


Enemy1::~Enemy1()
{
}
