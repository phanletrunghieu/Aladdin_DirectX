#pragma once

#include "../EnemyState.h"
#include "../../Weapons/EnemiesWeapons/Enemy3Weapon.h"
#include "../../../GameComponents/SceneManager.h"

class Enemy4IdleState : public EnemyState
{
public:
	Enemy4IdleState();
	Enemy4IdleState(Enemy* enemy);
	~Enemy4IdleState();

	void Update(float deltaTime);
};

