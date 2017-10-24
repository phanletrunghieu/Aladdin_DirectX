#pragma once

#include "PlayerState.h"
#include "PlayerRunFallState.h"
#include "PlayerJumpAttackState.h"
#include "PlayerJumpThrowState.h"

class PlayerRunJumpState : public PlayerState
{
public:
	PlayerRunJumpState();
	PlayerRunJumpState(Player* player);
	~PlayerRunJumpState();

	void Update(float deltaTime);
};

