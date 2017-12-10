#include "PlayerAttackState.h"
#include "Player.h"
#include "PlayerIdleState.h"
#include "../../GameComponents/Sound.h"

PlayerAttackState::PlayerAttackState()
{
	//don't use
}

PlayerAttackState::PlayerAttackState(Player * player) : PlayerState(player, PlayerState::StateName::Attack)
{
	SetAnimation(new Animation(ResourceManager::GetInstance()->GetAnimationXMLAladdin(), "Attack", ResourceManager::GetInstance()->GetTextureAladdin(), true, 0.5f));
	Sound::GetInstance()->Play("Low_Sword", 0, 1);
}


PlayerAttackState::~PlayerAttackState()
{
}

void PlayerAttackState::Update(float deltaTime)
{
	PlayerState::Update(deltaTime);

	if (_animation->IsFinish())//change state
	{
		_player->SetState(new PlayerIdleState(_player));
		return;
	}
}
