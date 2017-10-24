#pragma once

#include "../GameObject.h"
#include "../../GameComponents/Sprite.h"

class Apple : public GameObject
{
private:
	Sprite *_appleSprite;
public:
	Apple();
	~Apple();

	//void Update(float deltaTime);
	void Draw(Camera* camera);

	void OnCollision(GameObject *target, GameCollision::SideCollisions side);
};

