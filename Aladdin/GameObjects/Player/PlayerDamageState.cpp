#include "PlayerDamageState.h"
#include "Player.h"


PlayerDamageState::PlayerDamageState()
{
	//don't use
}

PlayerDamageState::PlayerDamageState(Player * player) : PlayerState(player, PlayerState::StateName::Damage)
{
	SetAnimation(new Animation(ResourceManager::GetInstance()->GetAnimationXMLAladdin(), "Damage", ResourceManager::GetInstance()->GetTextureAladdin(), true, 0.5f, false));
}


PlayerDamageState::~PlayerDamageState()
{
}

void PlayerDamageState::Update(float deltaTime)
{
	PlayerState::Update(deltaTime);

	if (_animation->IsFinish())//change state
	{
		_player->SetState(new PlayerIdleState(_player));
		return;
	}
}
