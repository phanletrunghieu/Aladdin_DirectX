#pragma once

#include "../Enemy.h"

class Jafar :public Enemy
{
public:
	Jafar();
	~Jafar();
	Jafar(GameObject * target);

	void Update(float deltatime);
};