#pragma once

#include "../Enemy.h"
#include "Enemy2IdleState.h"
#include "Enemy2Damage1State.h"

class Enemy2 : public Enemy
{
private:
	//used to check when injured
	int _prevHealth;
public:
	Enemy2();
	Enemy2(GameObject * player);
	~Enemy2();

	void Update(float deltaTime);
};