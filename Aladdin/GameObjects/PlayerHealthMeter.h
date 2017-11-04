#pragma once

#include "../GameComponents/Animation.h"
#include "GameObject.h"

class PlayerHealthMeter : public GameObject
{
private:
	Animation *_currentAnimation,
		*_animation10,
		*_animation9,
		*_animation8,
		*_animation7,
		*_animation6,
		*_animation5,
		*_animation4,
		*_animation3,
		*_animation2,
		*_animation1,
		*_animation0;
public:
	PlayerHealthMeter();
	~PlayerHealthMeter();

	void Draw(D3DXVECTOR3 position);
	void Update(float deltaTime);

	void ChangeAnimation(int value);
};

