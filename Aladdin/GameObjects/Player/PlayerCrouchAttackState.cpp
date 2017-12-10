#include "PlayerCrouchAttackState.h"
#include "Player.h"
#include "PlayerCrouchIdleState.h"
#include "../../GameComponents/Sound.h"

PlayerCrouchAttackState::PlayerCrouchAttackState()
{
}

PlayerCrouchAttackState::PlayerCrouchAttackState(Player * player) :PlayerState(player, PlayerState::StateName::CrouchAttack)
{
	SetAnimation(new Animation(ResourceManager::GetInstance()->GetAnimationXMLAladdin(), "CrouchAttack", ResourceManager::GetInstance()->GetTextureAladdin(), true, 0.5f));
	Sound::GetInstance()->Play("Low_Sword", 0, 1);
}


PlayerCrouchAttackState::~PlayerCrouchAttackState()
{
}

void PlayerCrouchAttackState::Update(float deltaTime)
{
	PlayerState::Update(deltaTime);

	if (_animation->IsFinish())//change state
	{
		PlayerCrouchIdleState* crouchIdle = new PlayerCrouchIdleState(_player);
		crouchIdle->GetAnimation()->SeekToLastFrame();
		_player->SetState(crouchIdle);
		return;
	}
}
