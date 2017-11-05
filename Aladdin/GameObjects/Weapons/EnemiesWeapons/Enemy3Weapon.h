#pragma once

#include "../Weapon.h"
#include "../../../GameComponents/Animation.h"

class Enemy3Weapon : public Weapon
{
private:
	Animation *_animation;
public:
	Enemy3Weapon(int damage = 10);
	~Enemy3Weapon();

	void Draw(Camera* camera);
	void Update(float deltaTime);

	void OnCollision(GameObject *target, GameCollision::SideCollisions side);
};

