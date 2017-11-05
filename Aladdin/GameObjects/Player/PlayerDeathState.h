#pragma once

#include "PlayerState.h"
#include "PlayerIdleState.h"

class PlayerDeathState : public PlayerState
{
public:
	PlayerDeathState();
	PlayerDeathState(Player* player);
	~PlayerDeathState();

	void Update(float deltaTime);
};

