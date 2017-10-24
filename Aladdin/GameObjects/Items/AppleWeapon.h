#pragma once

#include "../GameObject.h"
#include "../../GameComponents/Animation.h"

class AppleWeapon : public GameObject
{
private:
	Animation *_currentAnimation, *_animationFly, *_animationExplode;
public:
	AppleWeapon();
	~AppleWeapon();

	void Draw(Camera* camera);
	void Update(float deltaTime);

	void OnCollision(GameObject *target, GameCollision::SideCollisions side);
};

