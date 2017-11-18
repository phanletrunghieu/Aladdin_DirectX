#pragma once

#include "PlayerState.h"

class PlayerClimbVerticalState : public PlayerState
{
private:
	GameObject *_rope;
public:
	PlayerClimbVerticalState();
	PlayerClimbVerticalState(Player* player, GameObject *rope);
	~PlayerClimbVerticalState();

	void Update(float deltaTime);
};

