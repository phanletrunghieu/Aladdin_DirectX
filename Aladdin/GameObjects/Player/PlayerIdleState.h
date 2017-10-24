#pragma once

#include "PlayerState.h"
#include "PlayerRunState.h"
#include "PlayerAttackState.h"
#include "PlayerThrowState.h"
#include "PlayerJumpState.h"
#include "PlayerCrouchIdleState.h"

class PlayerIdleState : public PlayerState
{
public:
	PlayerIdleState();
	PlayerIdleState(Player* player);
	~PlayerIdleState();

	void Update(float deltaTime);
};

