#pragma once

#include "../GameObject.h"
#include "../../GameComponents/Sprite.h"

class FloatGround : public GameObject
{
private:
	Sprite *_floatGroundSprite;
public:
	FloatGround();
	~FloatGround();

	void Draw(Camera* camera);
};

