#pragma once

#include "../GameObject.h"
#include "../../GameComponents/Sprite.h"

class Springboard : public GameObject
{
private:
	Sprite *_springboardSprite;
public:
	Springboard();
	~Springboard();

	void Draw(Camera* camera);
};

