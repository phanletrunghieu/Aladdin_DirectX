#pragma once

#include "../GameObject.h"
#include "../../GameComponents/Animation.h"

class Coal : public GameObject
{
private:
	Animation* _animationCoalToFire;
	bool _isDrawFire, _isUpdateFire;
public:
	Coal();
	~Coal();

	void Update(float deltaTime);
	void Draw(Camera *camera);

	void OnCollision(GameObject *target, GameCollision::SideCollisions side);
};