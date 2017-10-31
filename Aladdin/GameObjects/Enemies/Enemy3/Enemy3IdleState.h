#pragma once

#include "../EnemyState.h"
#include "Enemy3WalkState.h"
#include "Enemy3AttackState.h"

class Enemy3IdleState : public EnemyState
{
public:
	Enemy3IdleState();
	Enemy3IdleState(Enemy* enemy);
	~Enemy3IdleState();

	void Update(float deltaTime);
};

