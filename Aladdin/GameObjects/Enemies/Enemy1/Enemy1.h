#pragma once

#include "../Enemy.h"
#include "Enemy1IdleState.h"
#include "Enemy1DamageState.h"

class Enemy1 : public Enemy
{
private:
	//used to check when injured
	int _prevHealth;
public:
	Enemy1();
	Enemy1(GameObject * player);
	~Enemy1();

	void Update(float deltaTime);
};