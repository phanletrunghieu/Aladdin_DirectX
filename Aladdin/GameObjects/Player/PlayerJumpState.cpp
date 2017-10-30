#include "PlayerJumpState.h"
#include "Player.h"

PlayerJumpState::PlayerJumpState()
{
	//don't use
}

PlayerJumpState::PlayerJumpState(Player * player) : PlayerState(player, PlayerState::StateName::Jump)
{
	SetAnimation(new Animation(ResourceManager::GetInstance()->GetAnimationXMLAladdin(), "Jump", ResourceManager::GetInstance()->GetTextureAladdin(), 0.8f, false));

	//TODO: fix jump continuously (Jump->Attack->Jump)
	if (_player->GetVelocity().y == 0)
		_player->SetVelocityY(-1 * _player->GetJumpForce());
	_player->SetAccelerationY(_player->GetMass());
}


PlayerJumpState::~PlayerJumpState()
{
}

void PlayerJumpState::Update(float deltaTime)
{
	PlayerState::Update(deltaTime);

	if (_player->GetVelocity().y > 0)
	{
		_player->SetState(new PlayerFallState(_player));
		return;
	}

	if (Input::GetInstance()->IsKeyPressed(DIK_S))
	{
		_player->SetState(new PlayerJumpAttackState(_player));
		return;
	}

	if (Input::GetInstance()->IsKeyPressed(DIK_A))
	{
		_player->SetState(new PlayerJumpThrowState(_player));
		return;
	}
}
