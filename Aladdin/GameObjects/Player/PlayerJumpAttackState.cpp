#include "PlayerJumpAttackState.h"
#include "Player.h"

PlayerJumpAttackState::PlayerJumpAttackState()
{
}

PlayerJumpAttackState::PlayerJumpAttackState(Player * player) : PlayerState(player, PlayerState::StateName::JumpAttack)
{
	_animation = new Animation(ResourceManager::GetInstance()->GetAnimationXMLAladdin(), "JumpAttack", ResourceManager::GetInstance()->GetTextureAladdin(), 0.5f);
	_animation->FlipHorizontal(!_player->IsRight());

	_animation->SetPosition(_player->GetPosition());
	_player->SetWidth(_animation->GetWidth());
	_player->SetHeight(_animation->GetHeight());
}


PlayerJumpAttackState::~PlayerJumpAttackState()
{
}

void PlayerJumpAttackState::Update(float deltaTime)
{
	PlayerState::Update(deltaTime);

	if (_animation->IsFinish())//change state
	{
		D3DXVECTOR2 playerVelocity = _player->GetVelocity();
		if (playerVelocity.x == 0)
		{
			if (playerVelocity.y < 0)
			{
				_player->SetState(new PlayerJumpState(_player));
			}
			else
			{
				_player->SetState(new PlayerFallState(_player));
			}
		}
		else
		{
			if (playerVelocity.y < 0)
			{
				_player->SetState(new PlayerRunJumpState(_player));
			}
			else
			{
				_player->SetState(new PlayerRunFallState(_player));
			}
		}
	}
}
