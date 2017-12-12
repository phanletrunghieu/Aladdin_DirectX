#pragma once

#include "ScoreObject.h"
#include "../../../GameComponents/Sprite.h"

class ScoreObject1 : public ScoreObject
{
private:
	Sprite *_sprite;
public:
	ScoreObject1(int score = 150);
	~ScoreObject1();

	void Draw(Camera* camera);
};

