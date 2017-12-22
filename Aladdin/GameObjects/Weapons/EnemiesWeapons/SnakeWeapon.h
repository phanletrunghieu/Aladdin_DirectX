#pragma once

#include "../Weapon.h"
#include "../../../GameComponents/Animation.h"
#include "../../../GameObjects/Items/Coal.h"

class SnakeWeapon :public Weapon
{
private:
	Animation * _animation;
public:
	SnakeWeapon(int damage = 10);
	~SnakeWeapon();

	void Draw(Camera *camera);
	void Update(float deltatime);

	void OnCollision(GameObject *target, GameCollision::SideCollisions side);
};