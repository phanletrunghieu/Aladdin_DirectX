#pragma once

#include "PlayerState.h"

class PlayerRunFallState : public PlayerState
{
public:
	PlayerRunFallState();
	PlayerRunFallState(Player* player);
	~PlayerRunFallState();

	void Update(float deltaTime);
	void OnCollision(GameObject *target, GameCollision::SideCollisions side);
};

