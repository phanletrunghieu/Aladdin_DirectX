#pragma once

#include "../EnemyState.h"

class Enemy5LookState : public EnemyState
{
public:
	Enemy5LookState();
	Enemy5LookState(Enemy* enemy);
	~Enemy5LookState();

	void Update(float deltaTime);
};

