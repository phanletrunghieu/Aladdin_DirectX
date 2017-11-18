#pragma once

#include "PlayerState.h"

class PlayerClimbHorizontalMoveState : public PlayerState
{
private:
	GameObject *_horizontalBar;
public:
	PlayerClimbHorizontalMoveState();
	PlayerClimbHorizontalMoveState(Player* player, GameObject *horizontalBar);
	~PlayerClimbHorizontalMoveState();

	void Update(float deltaTime);
};

