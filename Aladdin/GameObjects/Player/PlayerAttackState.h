#pragma once

#include "PlayerState.h"
#include "PlayerIdleState.h"

class PlayerAttackState : public PlayerState
{
public:
	PlayerAttackState();
	PlayerAttackState(Player* player);
	~PlayerAttackState();

	void Update(float deltaTime);
};

