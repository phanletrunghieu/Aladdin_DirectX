#pragma once

#include "../Enemy.h"

class Enemy3 : public Enemy
{
public:
	Enemy3();
	Enemy3(GameObject * player);
	~Enemy3();
};