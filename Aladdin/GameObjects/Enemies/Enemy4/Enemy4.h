#pragma once

#include "../Enemy.h"
#include "Enemy4IdleState.h"

class Enemy4 : public Enemy
{
public:
	Enemy4();
	Enemy4(GameObject * player);
	~Enemy4();
};