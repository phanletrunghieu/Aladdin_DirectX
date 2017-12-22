#include "PlayerRunState.h"
#include "Player.h"
#include "PlayerStopState.h"
#include "PlayerAttackState.h"
#include "PlayerThrowState.h"
#include "PlayerRunJumpState.h"
#include "PlayerRunFallState.h"

PlayerRunState::PlayerRunState()
{
}

PlayerRunState::PlayerRunState(Player * player) : PlayerState(player, PlayerState::StateName::Run)
{
	SetAnimation(new Animation(ResourceManager::GetInstance()->GetAnimationXMLAladdin(), "Run", ResourceManager::GetInstance()->GetTextureAladdin(), true, 1.0f));
}


PlayerRunState::~PlayerRunState()
{
}

void PlayerRunState::Update(float deltaTime)
{
	PlayerState::Update(deltaTime);

	if (_player->GetVelocity().x == 0)//change state
	{
		_player->SetState(new PlayerStopState(_player));
		return;
	}

	if (Input::GetInstance()->IsKeyPressed(DIK_D))
	{
		_player->SetState(new PlayerRunJumpState(_player));
		return;
	}

	if (Input::GetInstance()->IsKeyPressed(DIK_A) && _player->GetNumAppleWeapon() > 0)
	{
		_player->SetState(new PlayerThrowState(_player));
		return;
	}

	if (!_player->IsGround())
	{
		_player->SetState(new PlayerRunFallState(_player));
		return;
	}
}
