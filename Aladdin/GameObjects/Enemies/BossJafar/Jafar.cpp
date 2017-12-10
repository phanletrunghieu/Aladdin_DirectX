#include "Jafar.h"
#include "../../Player/Player.h"
#include "JafarAttack.h"

Jafar::Jafar()
{
	//not use
}

Jafar::~Jafar()
{
	delete _state;
	_state = 0;
}

Jafar::Jafar(GameObject * target) :Enemy(target)
{
	_health = 300;

	_isRight = false;
	_isMovableObject = false;

	_state = new JafarAttack(this);
	_allowUpdateWhenNotInCamera = true;
}

void Jafar::Update(float deltatime)
{
	Enemy::Update(deltatime);
}