#pragma once

#include "../EnemyState.h"

class Enemy5WalkState : public EnemyState
{
public:
	Enemy5WalkState();
	Enemy5WalkState(Enemy* enemy);
	~Enemy5WalkState();

	void Update(float deltaTime);
};

