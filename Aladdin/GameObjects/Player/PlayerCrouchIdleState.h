#pragma once

#include "PlayerState.h"

class PlayerCrouchIdleState : public PlayerState
{
public:
	PlayerCrouchIdleState();
	PlayerCrouchIdleState(Player* player);
	~PlayerCrouchIdleState();

	void Update(float deltaTime);
};

