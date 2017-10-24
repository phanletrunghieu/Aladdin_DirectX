#pragma once

#include "PlayerState.h"
#include "PlayerIdleState.h"

class PlayerStopState:public PlayerState
{
public:
	PlayerStopState();
	PlayerStopState(Player* player);
	~PlayerStopState();

	void Update(float deltaTime);
};

