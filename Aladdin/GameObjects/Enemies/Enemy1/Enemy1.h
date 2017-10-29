#pragma once

#include "../Enemy.h"
#include "Enemy1IdleState.h"

class Enemy1 : public Enemy
{
public:
	Enemy1();
	Enemy1(GameObject * player);
	~Enemy1();
};