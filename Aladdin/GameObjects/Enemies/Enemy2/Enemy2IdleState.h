#pragma once

#include "../EnemyState.h"
#include "Enemy2WalkState.h"
#include "Enemy2AttackState.h"

class Enemy2IdleState : public EnemyState
{
public:
	Enemy2IdleState();
	Enemy2IdleState(Enemy* enemy);
	~Enemy2IdleState();

	void Update(float deltaTime);
};

