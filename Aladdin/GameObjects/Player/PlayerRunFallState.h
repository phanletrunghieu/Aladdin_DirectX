#pragma once

#include "PlayerState.h"
#include "PlayerRunState.h"
#include "PlayerIdleState.h"
#include "PlayerJumpAttackState.h"
#include "PlayerJumpThrowState.h"
#include "PlayerClimbVerticalState.h"
#include "PlayerSpringState.h"

class PlayerRunFallState : public PlayerState
{
public:
	PlayerRunFallState();
	PlayerRunFallState(Player* player);
	~PlayerRunFallState();

	void Update(float deltaTime);
	void OnCollision(GameObject *target, GameCollision::SideCollisions side);
};

