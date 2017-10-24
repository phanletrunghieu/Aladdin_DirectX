#pragma once

#include "PlayerState.h"

class PlayerCrouchAttackState : public PlayerState
{
public:
	PlayerCrouchAttackState();
	PlayerCrouchAttackState(Player* player);
	~PlayerCrouchAttackState();

	void Update(float deltaTime);
};

