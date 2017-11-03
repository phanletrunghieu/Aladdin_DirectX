#pragma once

#include "../Enemy.h"
#include "Enemy5IdleState.h"

class Enemy5 : public Enemy
{
public:
	Enemy5();
	Enemy5(GameObject * player);
	~Enemy5();
};