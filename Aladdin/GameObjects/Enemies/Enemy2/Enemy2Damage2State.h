#pragma once

#include "../EnemyState.h"
#include "Enemy2AttackState.h"

class Enemy2Damage2State : public EnemyState
{
public:
	Enemy2Damage2State();
	Enemy2Damage2State(Enemy* enemy);
	~Enemy2Damage2State();

	void Update(float deltaTime);
};

