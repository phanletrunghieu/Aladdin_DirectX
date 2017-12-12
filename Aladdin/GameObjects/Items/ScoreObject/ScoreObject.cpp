#include "ScoreObject.h"

ScoreObject::ScoreObject(int score) : GameObject(GameObject::GameObjectType::ScoreObjects, true)
{
	_score = score;
}


ScoreObject::~ScoreObject()
{
}

int ScoreObject::GetScore()
{
	return _score;
}

void ScoreObject::SetScore(int score)
{
	_score = score;
}
