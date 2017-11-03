#pragma once

#include "../EnemyState.h"

class Enemy5AttackState : public EnemyState
{
public:
	Enemy5AttackState();
	Enemy5AttackState(Enemy* enemy);
	~Enemy5AttackState();

	void Update(float deltaTime);
};

