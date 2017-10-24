#pragma once

#include "PlayerState.h"
#include "PlayerFallState.h"

class PlayerSpringState : public PlayerState
{
public:
	PlayerSpringState();
	PlayerSpringState(Player* player);
	~PlayerSpringState();

	void Update(float deltaTime);
	void OnCollision(GameObject *target, GameCollision::SideCollisions side);
};

