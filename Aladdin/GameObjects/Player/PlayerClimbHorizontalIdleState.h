#pragma once

#include "PlayerState.h"
#include "PlayerClimbHorizontalMoveState.h"
#include "PlayerClimbAttackState.h"

class PlayerClimbHorizontalIdleState : public PlayerState
{
private:
	GameObject *_horizontalBar;
public:
	PlayerClimbHorizontalIdleState();
	PlayerClimbHorizontalIdleState(Player* player, GameObject *horizontalBar);
	~PlayerClimbHorizontalIdleState();

	void Update(float deltaTime);
};

