#pragma once

#include "../EnemyState.h"

class Enemy1AttackState : public EnemyState
{
public:
	Enemy1AttackState();
	Enemy1AttackState(Enemy* enemy);
	~Enemy1AttackState();

	void Update(float deltaTime);
};

