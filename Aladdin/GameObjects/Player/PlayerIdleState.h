#pragma once

#include "PlayerState.h"

class PlayerIdleState : public PlayerState
{
private:
	//used to check when player's injured
	int _prevHealth;
public:
	PlayerIdleState();
	PlayerIdleState(Player* player);
	~PlayerIdleState();

	void Update(float deltaTime);
};

