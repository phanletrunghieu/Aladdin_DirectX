#pragma once

#include "../EnemyState.h"

class Enemy4IdleState : public EnemyState
{
public:
	Enemy4IdleState();
	Enemy4IdleState(Enemy* enemy);
	~Enemy4IdleState();

	void Update(float deltaTime);
};

