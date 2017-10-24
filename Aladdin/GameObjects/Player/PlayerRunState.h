#pragma once

#include "PlayerState.h"
#include "PlayerStopState.h"
#include "PlayerRunJumpState.h"
#include "PlayerRunFallState.h"

class PlayerRunState:public PlayerState
{
public:
	PlayerRunState();
	PlayerRunState(Player* player);
	~PlayerRunState();

	void Update(float deltaTime);
};

