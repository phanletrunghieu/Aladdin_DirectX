#pragma once

#include "../EnemyState.h"

class Enemy6ThrowState : public EnemyState
{
private:
	bool _isCreatedWeapon;
public:
	Enemy6ThrowState();
	Enemy6ThrowState(Enemy* enemy);
	~Enemy6ThrowState();

	void Update(float deltaTime);
};