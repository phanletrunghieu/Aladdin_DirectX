#pragma once

#include "../EnemyState.h"
#include "Enemy5WalkState.h"
#include "Enemy5LookState.h"

class Enemy5IdleState : public EnemyState
{
public:
	Enemy5IdleState();
	Enemy5IdleState(Enemy* enemy);
	~Enemy5IdleState();

	void Update(float deltaTime);
};

