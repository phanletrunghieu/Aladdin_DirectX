#pragma once

#include "../EnemyState.h"
#include "../../Weapons/EnemiesWeapons/JafarWeapon.h"
#include "../../../GameComponents/SceneManager.h"

class JafarAttack :public EnemyState
{
private:
	bool _isCreatedWeapon;
	D3DXVECTOR2 _distanceToTarget;
public:
	JafarAttack();
	~JafarAttack();
	JafarAttack(Enemy* jafar);

	void Update(float deltatime);
};