#pragma once

#include "PlayerState.h"

class PlayerAttackState : public PlayerState
{
public:
	PlayerAttackState();
	PlayerAttackState(Player* player);
	~PlayerAttackState();

	void Update(float deltaTime);
};

