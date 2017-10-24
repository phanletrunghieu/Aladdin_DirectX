#include "PlayerRunState.h"
#include "Player.h"

PlayerRunState::PlayerRunState()
{
}

PlayerRunState::PlayerRunState(Player * player) : PlayerState(player, PlayerState::StateName::Run)
{
	_animation = new Animation(ResourceManager::GetInstance()->GetAladdinAnimationXML(), "Run", ResourceManager::GetInstance()->GetAladdinTexture(), 0.7f);
	_animation->FlipVertical(!_player->IsRight());

	_animation->SetPosition(_player->GetPosition());
	_player->SetWidth(_animation->GetWidth());
	_player->SetHeight(_animation->GetHeight());
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

	if (!_player->IsGround())
	{
		_player->SetState(new PlayerRunFallState(_player));
		return;
	}
}
