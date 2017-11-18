#pragma once

#include "../EnemyState.h"

class Enemy1WalkState : public EnemyState
{
public:
	Enemy1WalkState();
	Enemy1WalkState(Enemy* enemy);
	~Enemy1WalkState();

	void Update(float deltaTime);
};

