#pragma once

#include "PlayerState.h"

class PlayerFallState : public PlayerState
{
public:
	PlayerFallState();
	PlayerFallState(Player* player);
	~PlayerFallState();

	void Update(float deltaTime);
	void OnCollision(GameObject *target, GameCollision::SideCollisions side);
};

