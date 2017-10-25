#include "PlayerRunJumpState.h"
#include "Player.h"


PlayerRunJumpState::PlayerRunJumpState()
{
}

PlayerRunJumpState::PlayerRunJumpState(Player * player) : PlayerState(player, PlayerState::StateName::RunJump)
{
	_animation = new Animation(ResourceManager::GetInstance()->GetAnimationXMLAladdin(), "RunJump", ResourceManager::GetInstance()->GetTextureAladdin(), 0.8f);
	_animation->FlipHorizontal(!_player->IsRight());

	_animation->SetPosition(_player->GetPosition());
	_player->SetWidth(_animation->GetWidth());
	_player->SetHeight(_animation->GetHeight());

	//TODO: fix jump continuously (Jump->Attack->Jump)
	if (_player->GetVelocity().y == 0)
		_player->SetVelocityY(-1 * _player->GetJumpRunForce());
	_player->SetAccelerationY(_player->GetMass());
}


PlayerRunJumpState::~PlayerRunJumpState()
{
}

void PlayerRunJumpState::Update(float deltaTime)
{
	PlayerState::Update(deltaTime);

	if (_player->GetVelocity().y > 0)
	{
		_player->SetState(new PlayerRunFallState(_player));
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
