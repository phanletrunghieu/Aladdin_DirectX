#pragma once

#include "../EnemyState.h"
#include "Enemy1WalkState.h"
#include "Enemy1AttackState.h"

class Enemy1IdleState : public EnemyState
{
public:
	Enemy1IdleState();
	Enemy1IdleState(Enemy* enemy);
	~Enemy1IdleState();

	void Update(float deltaTime);
};

