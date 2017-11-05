#pragma once

#include "PlayerState.h"
#include "../Weapons/PlayerWeapons/AppleWeapon.h"
#include "../../GameComponents/SceneManager.h"

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

