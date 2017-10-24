#pragma once

#include "PlayerState.h"
#include "PlayerCrouchAttackState.h"

class PlayerCrouchIdleState : public PlayerState
{
public:
	PlayerCrouchIdleState();
	PlayerCrouchIdleState(Player* player);
	~PlayerCrouchIdleState();

	void Update(float deltaTime);
};

