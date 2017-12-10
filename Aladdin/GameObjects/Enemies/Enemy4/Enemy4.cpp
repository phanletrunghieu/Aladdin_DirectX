#include "Enemy4.h"
#include "Enemy4IdleState.h"

Enemy4::Enemy4()
{
	// not use
}

Enemy4::Enemy4(GameObject * player):Enemy(player)
{
	_state = new Enemy4IdleState(this);

	_attackRangeX = 180;
	_attackRangeY = 180;

	_isMovableObject = false;
	_canFlip = false;
}


Enemy4::~Enemy4()
{
}