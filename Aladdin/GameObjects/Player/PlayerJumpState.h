#pragma once

#include "PlayerState.h"
#include "PlayerFallState.h"
#include "PlayerJumpAttackState.h"
#include "PlayerJumpThrowState.h"

class PlayerJumpState : public PlayerState
{
public:
	PlayerJumpState();
	PlayerJumpState(Player* player);
	~PlayerJumpState();

	void Update(float deltaTime);
};

