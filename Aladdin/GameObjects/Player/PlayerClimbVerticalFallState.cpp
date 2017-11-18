#include "PlayerClimbVerticalFallState.h"
#include "Player.h"
#include "PlayerClimbHorizontalIdleState.h"
#include "PlayerClimbVerticalState.h"
#include "PlayerFallState.h"

PlayerClimbVerticalFallState::PlayerClimbVerticalFallState()
{
}

PlayerClimbVerticalFallState::PlayerClimbVerticalFallState(Player * player) : PlayerState(player, PlayerState::StateName::ClimbVerticalFall)
{
	SetAnimation(new Animation(ResourceManager::GetInstance()->GetAnimationXMLAladdin(), "ClimbVerticalFall", ResourceManager::GetInstance()->GetTextureAladdin(), true, 0.8f));

	_player->SetAccelerationY(_player->GetMass());
}


PlayerClimbVerticalFallState::~PlayerClimbVerticalFallState()
{
}

void PlayerClimbVerticalFallState::Update(float deltaTime)
{
	PlayerState::Update(deltaTime);

	if (_animation->IsFinish())
	{
		_player->SetState(new PlayerFallState(_player));
		return;
	}
}

void PlayerClimbVerticalFallState::OnCollision(GameObject * target, GameCollision::SideCollisions side)
{
	PlayerState::OnCollision(target, side);

	if (target->GetTag() == GameObject::GameObjectType::Rope)
	{
		float diffX = abs(target->GetPosition().x - _player->GetPosition().x);
		if (diffX < 18 && _player->GetBound().bottom <= target->GetBound().bottom && _player->GetBound().top >= target->GetBound().top)
		{
			_player->SetState(new PlayerClimbVerticalState(_player, target));
		}
	}

	if (target->GetTag() == GameObject::GameObjectType::HorizontalBar)
	{
		float diffTop = abs(target->GetBound().top - _player->GetBound().top);
		if (diffTop < 18
			&& _player->GetPosition().x >= target->GetBound().left
			&& _player->GetPosition().x <= target->GetBound().right)
			_player->SetState(new PlayerClimbHorizontalIdleState(_player, target), false);
	}
}
