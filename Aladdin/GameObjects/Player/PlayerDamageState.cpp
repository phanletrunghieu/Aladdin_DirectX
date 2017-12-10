#include "PlayerDamageState.h"
#include "Player.h"
#include "PlayerIdleState.h"
#include "PlayerAttackState.h"
#include "PlayerJumpState.h"
#include "PlayerThrowState.h"
#include "PlayerCrouchIdleState.h"

PlayerDamageState::PlayerDamageState()
{
	//don't use
}

PlayerDamageState::PlayerDamageState(Player * player) : PlayerState(player, PlayerState::StateName::Damage)
{
	SetAnimation(new Animation(ResourceManager::GetInstance()->GetAnimationXMLAladdin(), "Damage", ResourceManager::GetInstance()->GetTextureAladdin(), true, 0.5f, false));
}


PlayerDamageState::~PlayerDamageState()
{
}

void PlayerDamageState::Update(float deltaTime)
{
	PlayerState::Update(deltaTime);

	if (_animation->IsFinish())//change state
	{
		_player->SetState(new PlayerIdleState(_player));
		return;
	}

	//attack
	if (Input::GetInstance()->IsKeyPressed(DIK_S))
	{
		_player->SetState(new PlayerAttackState(_player));
		return;
	}

	//jump
	if (Input::GetInstance()->IsKeyPressed(DIK_D))
	{
		_player->SetState(new PlayerJumpState(_player));
		return;
	}

	//throw apple
	if (Input::GetInstance()->IsKeyPressed(DIK_A) && _player->GetNumAppleWeapon() > 0)
	{
		_player->SetState(new PlayerThrowState(_player));
		return;
	}

	//idle
	if (Input::GetInstance()->IsKeyPressed(DIK_DOWN))
	{
		_player->SetState(new PlayerCrouchIdleState(_player));
		return;
	}
}
