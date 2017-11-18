#pragma once

#include "PlayerState.h"

class PlayerThrowState : public PlayerState
{
private:
	bool _isCreatedAppleWeapon;
public:
	PlayerThrowState();
	PlayerThrowState(Player* player);
	~PlayerThrowState();

	void Update(float deltaTime);
};

