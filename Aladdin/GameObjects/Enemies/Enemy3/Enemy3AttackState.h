#pragma once

#include "../EnemyState.h"
#include "../../Weapons/EnemiesWeapons/Enemy3Weapon.h"
#include "../../../GameComponents/SceneManager.h"

class Enemy3AttackState : public EnemyState
{
private:
	bool _isCreatedWeapon;
public:
	Enemy3AttackState();
	Enemy3AttackState(Enemy* enemy);
	~Enemy3AttackState();

	void Update(float deltaTime);
};

