#include "PlayerClimbVerticalJumpState.h"
#include "Player.h"

PlayerClimbVerticalJumpState::PlayerClimbVerticalJumpState()
{
}

PlayerClimbVerticalJumpState::PlayerClimbVerticalJumpState(Player * player) : PlayerState(player, PlayerState::StateName::ClimbVerticalJump)
{
	_animation = new Animation(ResourceManager::GetInstance()->GetAnimationXMLAladdin(), "ClimbVerticalJump", ResourceManager::GetInstance()->GetTextureAladdin(), 0.8f);
	_animation->FlipHorizontal(!_player->IsRight());

	_animation->SetPosition(_player->GetPosition());
	_player->SetWidth(_animation->GetWidth());
	_player->SetHeight(_animation->GetHeight());

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