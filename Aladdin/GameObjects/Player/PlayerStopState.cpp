#include "PlayerStopState.h"
#include "Player.h"


PlayerStopState::PlayerStopState()
{
}

PlayerStopState::PlayerStopState(Player * player):PlayerState(player, PlayerState::StateName::Stop)
{
	_animation = new Animation(ResourceManager::GetInstance()->GetAladdinAnimationXML(), "Stop", ResourceManager::GetInstance()->GetAladdinTexture(), 0.4f);
	_animation->FlipVertical(!_player->IsRight());

	_animation->SetPosition(_player->GetPosition());
	_player->SetWidth(_animation->GetWidth());
	_player->SetHeight(_animation->GetHeight());
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
