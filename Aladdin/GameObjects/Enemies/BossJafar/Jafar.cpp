#include "Jafar.h"
#include "../../Player/Player.h"
#include "JafarAttack.h"
#include "../../../GameComponents/SceneManager.h"
#include "../../../Scenes/VictoryScene.h"

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
	_health = 500;

	_isRight = false;
	_isMovableObject = false;

	_state = new JafarAttack(this);
	_allowUpdateWhenNotInCamera = true;
}

void Jafar::Update(float deltatime)
{
	Enemy::Update(deltatime);

	if (_health <= 0)
	{
		SceneManager::GetInstance()->ReplaceScene(new VictoryScene());
		_state = NULL;
	}
}