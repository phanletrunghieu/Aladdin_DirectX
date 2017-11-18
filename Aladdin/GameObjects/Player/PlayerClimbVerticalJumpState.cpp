#include "PlayerClimbVerticalJumpState.h"
#include "Player.h"
#include "PlayerClimbVerticalFallState.h"

PlayerClimbVerticalJumpState::PlayerClimbVerticalJumpState()
{
}

PlayerClimbVerticalJumpState::PlayerClimbVerticalJumpState(Player * player) : PlayerState(player, PlayerState::StateName::ClimbVerticalJump)
{
	SetAnimation(new Animation(ResourceManager::GetInstance()->GetAnimationXMLAladdin(), "ClimbVerticalJump", ResourceManager::GetInstance()->GetTextureAladdin(), true, 0.8f));

	_player->SetVelocityY(-1 * _player->GetJumpForce());
	_player->SetAccelerationY(_player->GetMass());
}


PlayerClimbVerticalJumpState::~PlayerClimbVerticalJumpState()
{
}

void PlayerClimbVerticalJumpState::Update(float deltaTime)
{
	PlayerState::Update(deltaTime);

	if (_player->GetVelocity().y > 0)
	{
		_player->SetState(new PlayerClimbVerticalFallState(_player));
		return;
	}
}