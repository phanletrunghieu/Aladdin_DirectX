#pragma once

#include "../EnemyState.h"

class Enemy2AttackState : public EnemyState
{
private:
	Animation *_animationAttack1, *_animationAttack2;
public:
	Enemy2AttackState();
	Enemy2AttackState(Enemy* enemy);
	~Enemy2AttackState();

	void Update(float deltaTime);
};

