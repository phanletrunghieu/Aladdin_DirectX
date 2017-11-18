#pragma once

#include "PlayerState.h"

class PlayerRunJumpState : public PlayerState
{
public:
	PlayerRunJumpState();
	PlayerRunJumpState(Player* player);
	~PlayerRunJumpState();

	void Update(float deltaTime);
};

