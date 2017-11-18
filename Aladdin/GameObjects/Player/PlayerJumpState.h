#pragma once

#include "PlayerState.h"

class PlayerJumpState : public PlayerState
{
public:
	PlayerJumpState();
	PlayerJumpState(Player* player);
	~PlayerJumpState();

	void Update(float deltaTime);
};

