#pragma once

#include "PlayerState.h"

class PlayerJumpAttackState : public PlayerState
{
public:
	PlayerJumpAttackState();
	PlayerJumpAttackState(Player* player);
	~PlayerJumpAttackState();

	void Update(float deltaTime);
};

