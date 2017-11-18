#pragma once

#include "../EnemyState.h"
#include "../../Weapons/EnemiesWeapons/SnakeWeapon.h"
#include "../../../GameComponents/SceneManager.h"

class SnakeAttack : public EnemyState
{
private:
	bool _isCreatedWeapon;
public:
	SnakeAttack();
	~SnakeAttack();
	SnakeAttack(Enemy* Jafar);

	void Update(float deltatime);
};