#pragma once

#include "PlayerState.h"

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

