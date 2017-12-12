#pragma once

#include "../GameObject.h"
#include "../../GameComponents/Animation.h"

class Bottle : public GameObject
{
private:
	Animation *_animation;
public:
	Bottle();
	~Bottle();

	void Draw(Camera* camera);
	void Update(float deltaTime);

	void OnCollision(GameObject *target, GameCollision::SideCollisions side);
};

