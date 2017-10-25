#include "PlayerClimbHorizontalIdleState.h"
#include "Player.h"

PlayerClimbHorizontalIdleState::PlayerClimbHorizontalIdleState()
{
}

PlayerClimbHorizontalIdleState::PlayerClimbHorizontalIdleState(Player * player, GameObject *horizontalBar) : PlayerState(player, PlayerState::StateName::ClimbHorizontalIde)
{
	_animation = new Animation(ResourceManager::GetInstance()->GetAnimationXMLAladdin(), "ClimbHorizontalIde", ResourceManager::GetInstance()->GetTextureAladdin(), 1.8f);
	_animation->FlipHorizontal(!_player->IsRight());

	_animation->SetPosition(_player->GetPosition());
	_player->SetWidth(_animation->GetWidth());
	_player->SetHeight(_animation->GetHeight());

	_player->SetAccelerationY(0);
	_player->SetVelocityY(0);

	//fix position when jump over height
	_horizontalBar = horizontalBar;
	_player->SetPositionY(_horizontalBar->GetBound().top + _player->GetHeight() / 2.0f);
}


PlayerClimbHorizontalIdleState::~PlayerClimbHorizontalIdleState()
{
}

void PlayerClimbHorizontalIdleState::Update(float deltaTime)
{
	PlayerState::Update(deltaTime);

	//change state
	if (_player->GetVelocity().x != 0)
	{
		_player->SetState(new PlayerClimbHorizontalMoveState(_player, _horizontalBar));
		return;
	}

	if (Input::GetInstance()->IsKeyPressed(DIK_S))
	{
		_player->SetState(new PlayerClimbAttackState(_player, _horizontalBar, PlayerState::StateName::ClimbHorizontalIde));
		return;
	}

	if (Input::GetInstance()->IsKeyPressed(DIK_D))
	{
		//move player out of horizontal-bar (prevent loop idle->fall->idle)
		PlayerState *newState = new PlayerFallState(_player);
		_player->SetPositionY(_player->GetPosition().y + 20);
		_player->SetState(newState);
		return;
	}
}
