#pragma once

#include "../Weapon.h"
#include "../../../GameComponents/Animation.h"

class JafarWeapon : public Weapon
{
private:
	Animation *_animationFly, *_animationExploide;
public:
	JafarWeapon(int damage = 10);
	~JafarWeapon();

	void Draw(Camera* camera);
	void Update(float deltatime);

	void OnCollision(GameObject* target, GameCollision::SideCollisions side);
};