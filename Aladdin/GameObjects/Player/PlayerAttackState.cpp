#include "PlayerAttackState.h"
#include "Player.h"


PlayerAttackState::PlayerAttackState()
{
	//don't use
}

PlayerAttackState::PlayerAttackState(Player * player) : PlayerState(player, PlayerState::StateName::Attack)
{
	SetAnimation(new Animation(ResourceManager::GetInstance()->GetAnimationXMLAladdin(), "Attack", ResourceManager::GetInstance()->GetTextureAladdin(), 0.5f));
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
