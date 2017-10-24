#pragma once

#include "PlayerState.h"
#include "PlayerClimbAttackState.h"
#include "PlayerClimbVerticalJumpState.h"

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

