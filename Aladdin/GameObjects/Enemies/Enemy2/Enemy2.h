#pragma once

#include "../Enemy.h"
#include "Enemy2IdleState.h"

class Enemy2 : public Enemy
{
public:
	Enemy2();
	Enemy2(GameObject * player);
	~Enemy2();
};