#pragma once

#include "PlayerState.h"
#include "PlayerClimbVerticalFallState.h"

class PlayerClimbVerticalJumpState : public PlayerState
{
public:
	PlayerClimbVerticalJumpState();
	PlayerClimbVerticalJumpState(Player* player);
	~PlayerClimbVerticalJumpState();

	void Update(float deltaTime);
};

