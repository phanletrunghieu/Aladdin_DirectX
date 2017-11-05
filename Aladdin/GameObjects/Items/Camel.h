#pragma once

#include "../GameObject.h"
#include "../../GameComponents/Animation.h"
#include "../Player/Player.h"

class Camel : public GameObject
{
private:
	Animation *_animation;
public:
	Camel();
	~Camel();

	void Draw(Camera* camera);
	void Update(float deltaTime);

	void OnCollision(GameObject *target, GameCollision::SideCollisions side);
};

