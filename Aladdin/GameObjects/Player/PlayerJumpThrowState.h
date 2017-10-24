#pragma once

#include "PlayerState.h"

class PlayerJumpThrowState : public PlayerState
{
private:
	bool _isCreatedAppleWeapon;
public:
	PlayerJumpThrowState();
	PlayerJumpThrowState(Player* player);
	~PlayerJumpThrowState();

	void Update(float deltaTime);
};

