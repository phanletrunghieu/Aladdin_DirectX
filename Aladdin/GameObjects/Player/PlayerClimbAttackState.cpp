#include "PlayerClimbAttackState.h"
#include "Player.h"


PlayerClimbAttackState::PlayerClimbAttackState()
{
}

PlayerClimbAttackState::PlayerClimbAttackState(Player * player, GameObject *ropeOrHorizontalBar, PlayerState::StateName fromState) : PlayerState(player, PlayerState::StateName::ClimbAttack)
{
	_ropeOrHorizontalBar = ropeOrHorizontalBar;
	_fromState = fromState;

	_animation = new Animation(ResourceManager::GetInstance()->GetAnimationXMLAladdin(), "ClimbAttack", ResourceManager::GetInstance()->GetTextureAladdin(), 0.5f);
	_animation->FlipVertical(!_player->IsRight());

	_animation->SetPosition(_player->GetPosition());
	_player->SetWidth(_animation->GetWidth());
	_player->SetHeight(_animation->GetHeight());

	_player->SetAccelerationY(0);
	_player->SetVelocityY(0);

	_player->AllowMoveLeft(false);
	_player->AllowMoveRight(false);
}


PlayerClimbAttackState::~PlayerClimbAttackState()
{
}

void PlayerClimbAttackState::Update(float deltaTime)
{
	PlayerState::Update(deltaTime);

	if (_animation->IsFinish())//change state
	{
		if (_fromState == PlayerState::StateName::ClimbVertical)
			_player->SetState(new PlayerClimbVerticalState(_player, _ropeOrHorizontalBar));
		else if(_fromState == PlayerState::StateName::ClimbHorizontalIde)
			_player->SetState(new PlayerClimbHorizontalIdleState(_player, _ropeOrHorizontalBar));
		return;
	}
}
