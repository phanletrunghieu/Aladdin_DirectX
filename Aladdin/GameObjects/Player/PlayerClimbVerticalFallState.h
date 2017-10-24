#pragma once

#include "PlayerState.h"
#include "PlayerClimbHorizontalIdleState.h"

class PlayerClimbVerticalFallState : public PlayerState
{
public:
	PlayerClimbVerticalFallState();
	PlayerClimbVerticalFallState(Player* player);
	~PlayerClimbVerticalFallState();

	void Update(float deltaTime);
	void OnCollision(GameObject *target, GameCollision::SideCollisions side);
};

