#include "PlayerAttackState.h"
#include "Player.h"


PlayerAttackState::PlayerAttackState()
{
	//don't use
}

PlayerAttackState::PlayerAttackState(Player * player) : PlayerState(player, PlayerState::StateName::Attack)
{
	_animation = new Animation(ResourceManager::GetInstance()->GetAnimationXMLAladdin(), "Attack", ResourceManager::GetInstance()->GetTextureAladdin(), 0.5f);
	_animation->FlipVertical(!_player->IsRight());

	_animation->SetPosition(_player->GetPosition());
	_player->SetWidth(_animation->GetWidth());
	_player->SetHeight(_animation->GetHeight());
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
