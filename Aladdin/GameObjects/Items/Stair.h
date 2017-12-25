#pragma once

#include "../GameObject.h"

class Stair : public GameObject
{
private:
	//used to check if allow change the counter
	bool _allowIncreaseCounter;

	//counter: if %2==0 => check collision with player
	int _countCollision;

	//chieu di len la trai hay phai
	GameCollision::SideCollisions _side;
public:
	Stair(GameCollision::SideCollisions side);
	~Stair();

	void CheckCollision();
	void OnCollision(GameObject *target, GameCollision::SideCollisions side);

	void SetCounter(int counter);

	bool IsCheckCollisionAsGround();
	GameCollision::SideCollisions GetSide();
};

