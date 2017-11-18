#pragma once

#include "../EnemyState.h"

class Enemy2WalkState : public EnemyState
{
public:
	Enemy2WalkState();
	Enemy2WalkState(Enemy* enemy);
	~Enemy2WalkState();

	void Update(float deltaTime);
};

