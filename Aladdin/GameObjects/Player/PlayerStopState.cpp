#include "PlayerStopState.h"
#include "Player.h"
#include "PlayerIdleState.h"
#include "PlayerRunJumpState.h"


PlayerStopState::PlayerStopState()
{
}

PlayerStopState::PlayerStopState(Player * player):PlayerState(player, PlayerState::StateName::Stop)
{
	SetAnimation(new Animation(ResourceManager::GetInstance()->GetAnimationXMLAladdin(), "Stop", ResourceManager::GetInstance()->GetTextureAladdin(), true, 0.4f));
}


PlayerStopState::~PlayerStopState()
{
}

void PlayerStopState::Update(float deltaTime)
{
	PlayerState::Update(deltaTime);

	if (_animation->IsFinish())//change state
	{
		_player->SetState(new PlayerIdleState(_player));
		return;
	}

	if (Input::GetInstance()->IsKeyPressed(DIK_D))
	{
		_player->SetState(new PlayerRunJumpState(_player));
		return;
	}
}
