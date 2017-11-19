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
}

Jafar::Jafar(GameObject * target) :Enemy(target)
{
	_health = 300;
	_isRight = false;
	_canMove = false;
	_state = new JafarAttack(this);
}

void Jafar::Update(float deltatime)
{
	Enemy::Update(deltatime);
}