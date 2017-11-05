#include "PlayerDeathState.h"
#include "Player.h"


PlayerDeathState::PlayerDeathState()
{
	//don't use
}

PlayerDeathState::PlayerDeathState(Player * player) : PlayerState(player, PlayerState::StateName::Attack)
{
	SetAnimation(new Animation(ResourceManager::GetInstance()->GetAnimationXMLAladdin(), "Death", ResourceManager::GetInstance()->GetTextureAladdin(), true, 0.5f, false));
}


PlayerDeathState::~PlayerDeathState()
{
}

void PlayerDeathState::Update(float deltaTime)
{
	PlayerState::Update(deltaTime);
}
