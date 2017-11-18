#pragma once

#include "PlayerState.h"

class PlayerSpringState : public PlayerState
{
public:
	PlayerSpringState();
	PlayerSpringState(Player* player);
	~PlayerSpringState();

	void Update(float deltaTime);
	void OnCollision(GameObject *target, GameCollision::SideCollisions side);
};

