#include "PlayerCrouchIdleState.h"
#include "Player.h"

PlayerCrouchIdleState::PlayerCrouchIdleState()
{
}

PlayerCrouchIdleState::PlayerCrouchIdleState(Player * player) : PlayerState(player, PlayerState::StateName::CrouchIdle)
{
	SetAnimation(new Animation(ResourceManager::GetInstance()->GetAnimationXMLAladdin(), "CrouchIdle", ResourceManager::GetInstance()->GetTextureAladdin(), true, 0.4f, false));
}


PlayerCrouchIdleState::~PlayerCrouchIdleState()
{
}

void PlayerCrouchIdleState::Update(float deltaTime)
{
	PlayerState::Update(deltaTime);

	//change state
	if (!Input::GetInstance()->IsKeyPressed(DIK_DOWN))
	{
		//release key "down"->stand up (reverse animation)
		_animation->Reverse(true);

		//because current state is not loop->pause
		_animation->SetLoop(true);
		_animation->Play();
	}

	if (_animation->IsReverse() && _animation->IsBegin())
	{
		_player->SetState(new PlayerIdleState(_player));
		return;
	}

	if (Input::GetInstance()->IsKeyPressed(DIK_D))
	{
		_player->SetState(new PlayerJumpState(_player));
		return;
	}

	if (Input::GetInstance()->IsKeyPressed(DIK_S))
	{
		_player->SetState(new PlayerCrouchAttackState(_player));
		return;
	}
}
