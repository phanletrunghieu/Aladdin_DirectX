#pragma once

#include "../../GameObject.h"

class ScoreObject : public GameObject
{
protected:
	int _score;
public:
	ScoreObject(int score = 150);
	~ScoreObject();

	int GetScore();
	void SetScore(int score);
};

