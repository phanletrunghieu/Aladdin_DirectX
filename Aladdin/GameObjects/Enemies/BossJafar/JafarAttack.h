#pragma once

#include "../EnemyState.h"

class JafarAttack :public EnemyState
{
private:
	bool _isCreatedWeapon;
public:
	JafarAttack();
	~JafarAttack();
	JafarAttack(Enemy* jafar);

	void Update(float deltatime);
};