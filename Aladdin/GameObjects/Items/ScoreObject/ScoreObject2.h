#pragma once

#include "ScoreObject.h"
#include "../../../GameComponents/Sprite.h"

class ScoreObject2 : public ScoreObject
{
private:
	Sprite *_sprite;
public:
	ScoreObject2(int score = 100);
	~ScoreObject2();

	void Draw(Camera* camera);
};

