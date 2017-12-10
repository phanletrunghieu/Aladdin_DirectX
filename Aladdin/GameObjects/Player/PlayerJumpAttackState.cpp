#include "PlayerJumpAttackState.h"
#include "Player.h"
#include "PlayerJumpState.h"
#include "PlayerFallState.h"
#include "PlayerRunJumpState.h"
#include "PlayerRunFallState.h"
#include "../../GameComponents/Sound.h"

PlayerJumpAttackState::PlayerJumpAttackState()
{
}

PlayerJumpAttackState::PlayerJumpAttackState(Player * player) : PlayerState(player, PlayerState::StateName::JumpAttack)
{
	SetAnimation(new Animation(ResourceManager::GetInstance()->GetAnimationXMLAladdin(), "JumpAttack", ResourceManager::GetInstance()->GetTextureAladdin(), true, 0.5f));
	Sound::GetInstance()->Play("Low_Sword", 0, 1);
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
