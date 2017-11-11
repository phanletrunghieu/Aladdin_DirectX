#pragma once

#include "../EnemyState.h"

class Enemy1DamageState : public EnemyState
{
public:
	Enemy1DamageState();
	Enemy1DamageState(Enemy* enemy);
	~Enemy1DamageState();

	void Update(float deltaTime);
};

