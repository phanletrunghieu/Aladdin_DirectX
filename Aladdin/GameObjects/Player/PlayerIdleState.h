#pragma once

#include "PlayerState.h"
#include "PlayerRunState.h"
#include "PlayerAttackState.h"
#include "PlayerThrowState.h"
#include "PlayerJumpState.h"
#include "PlayerCrouchIdleState.h"
#include "PlayerDamageState.h"

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

