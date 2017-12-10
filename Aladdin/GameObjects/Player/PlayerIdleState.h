#pragma once

#include "PlayerState.h"

class PlayerIdleState : public PlayerState
{
public:
	PlayerIdleState();
	PlayerIdleState(Player* player);
	~PlayerIdleState();

	void Update(float deltaTime);
};

