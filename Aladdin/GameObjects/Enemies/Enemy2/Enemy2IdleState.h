#pragma once

#include "../EnemyState.h"

class Enemy2IdleState : public EnemyState
{
public:
	Enemy2IdleState();
	Enemy2IdleState(Enemy* enemy);
	~Enemy2IdleState();

	void Update(float deltaTime);
};

