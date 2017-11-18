#pragma once

#include "PlayerState.h"

class PlayerRunState:public PlayerState
{
public:
	PlayerRunState();
	PlayerRunState(Player* player);
	~PlayerRunState();

	void Update(float deltaTime);
};

