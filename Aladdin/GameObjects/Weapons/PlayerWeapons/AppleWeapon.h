#pragma once

#include "../Weapon.h"
#include "../../../GameComponents/Animation.h"

class AppleWeapon : public Weapon
{
private:
	Animation *_currentAnimation, *_animationFly, *_animationExplode;
public:
	AppleWeapon(int damage = 50);
	~AppleWeapon();

	void Draw(Camera* camera);
	void Update(float deltaTime);

	void OnCollision(GameObject *target, GameCollision::SideCollisions side);
};

