#include "PlayerSpringState.h"
#include "Player.h"

PlayerSpringState::PlayerSpringState()
{
}

PlayerSpringState::PlayerSpringState(Player * player) : PlayerState(player, PlayerState::StateName::Spring)
{
	SetAnimation(new Animation(ResourceManager::GetInstance()->GetAnimationXMLAladdin(), "Spring", ResourceManager::GetInstance()->GetTextureAladdin(), true, 0.4f));
	
	_player->SetVelocityY(-1 * _player->GetJumpForce()*1.3f);
	_player->SetAccelerationY(_player->GetMass());
}


PlayerSpringState::~PlayerSpringState()
{
}

void PlayerSpringState::Update(float deltaTime)
{
	PlayerState::Update(deltaTime);

	if (_player->IsGround())//change state
	{
		_player->SetState(new PlayerIdleState(_player));
		return;
	}

	if (_animation->IsFinish())
	{
		_player->SetState(new PlayerFallState(_player));
		return;
	}
}

void PlayerSpringState::OnCollision(GameObject * target, GameCollision::SideCollisions side)
{
	PlayerState::OnCollision(target, side);

	if (target->GetTag() == GameObject::GameObjectType::Springboard && _player->GetVelocity().y > 0)
	{
		float diffY = abs(target->GetPosition().y - _player->GetBound().bottom);//ko dung GetBound, ma lay positionY cua target vi target nam xieng
		if (diffY < 18)
		{
			_player->SetState(new PlayerSpringState(_player));
		}
	}
}
