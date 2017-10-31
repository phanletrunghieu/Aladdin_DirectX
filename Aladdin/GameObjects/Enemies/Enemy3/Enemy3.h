#pragma once

#include "../Enemy.h"
#include "Enemy3IdleState.h"

class Enemy3 : public Enemy
{
public:
	Enemy3();
	Enemy3(GameObject * player);
	~Enemy3();
};