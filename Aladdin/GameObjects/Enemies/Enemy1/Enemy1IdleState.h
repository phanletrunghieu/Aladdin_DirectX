#pragma once

#include "../EnemyState.h"

class Enemy1IdleState : public EnemyState
{
public:
	Enemy1IdleState();
	Enemy1IdleState(Enemy* enemy);
	~Enemy1IdleState();

	void Update(float deltaTime);
};

