#include "PlayerIdleState.h"
#include "Player.h"

PlayerIdleState::PlayerIdleState()
{
}

PlayerIdleState::PlayerIdleState(Player* player):PlayerState(player, PlayerState::StateName::Idle)
{
	SetAnimation(new Animation(ResourceManager::GetInstance()->GetAnimationXMLAladdin(), "Idle", ResourceManager::GetInstance()->GetTextureAladdin(), true, 1.8f));
}


PlayerIdleState::~PlayerIdleState()
{
}

void PlayerIdleState::Update(float deltaTime)
{
	PlayerState::Update(deltaTime);

	//change state
	if (_player->GetVelocity().x != 0)
	{
		_player->SetState(new PlayerRunState(_player));
		return;
	}

	if (Input::GetInstance()->IsKeyPressed(DIK_S))
	{
		_player->SetState(new PlayerAttackState(_player));
		return;
	}

	if (Input::GetInstance()->IsKeyPressed(DIK_D))
	{
		_player->SetState(new PlayerJumpState(_player));
		return;
	}

	if (Input::GetInstance()->IsKeyPressed(DIK_A))
	{
		_player->SetState(new PlayerThrowState(_player));
		return;
	}

	if (Input::GetInstance()->IsKeyPressed(DIK_DOWN))
	{
		_player->SetState(new PlayerCrouchIdleState(_player));
		return;
	}

	if (!_player->IsGround())
	{
		_player->SetState(new PlayerFallState(_player));
		return;
	}
}
