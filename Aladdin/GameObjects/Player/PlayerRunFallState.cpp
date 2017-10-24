#include "PlayerRunFallState.h"
#include "Player.h"


PlayerRunFallState::PlayerRunFallState()
{
	//don't use
}

PlayerRunFallState::PlayerRunFallState(Player * player) : PlayerState(player, PlayerState::StateName::RunFall)
{
	_animation = new Animation(ResourceManager::GetInstance()->GetAnimationXMLAladdin(), "RunFall", ResourceManager::GetInstance()->GetTextureAladdin(), 0.8f);
	_animation->FlipVertical(!_player->IsRight());

	_animation->SetPosition(_player->GetPosition());
	_player->SetWidth(_animation->GetWidth());
	_player->SetHeight(_animation->GetHeight());

	_player->SetAccelerationY(_player->GetMass());
}


PlayerRunFallState::~PlayerRunFallState()
{
}

void PlayerRunFallState::Update(float deltaTime)
{
	PlayerState::Update(deltaTime);

	if (_player->IsGround())//change state
	{
		if (_player->GetVelocity().x == 0)
			_player->SetState(new PlayerIdleState(_player));
		else
			_player->SetState(new PlayerRunState(_player));
		return;
	}

	if (Input::GetInstance()->IsKeyPressed(DIK_S))
	{
		_player->SetState(new PlayerJumpAttackState(_player));
		return;
	}

	if (Input::GetInstance()->IsKeyPressed(DIK_A))
	{
		_player->SetState(new PlayerJumpThrowState(_player));
		return;
	}
}

void PlayerRunFallState::OnCollision(GameObject * target, GameCollision::SideCollisions side)
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
			_player->SetState(new PlayerClimbHorizontalIdleState(_player, target));
	}

	if (target->GetTag() == GameObject::GameObjectType::Springboard)
	{
		float diffY = abs(target->GetPosition().y - _player->GetBound().bottom);//ko dung GetBound, ma lay positionY cua target vi target nam xieng
		if (diffY < 18)
		{
			_player->SetState(new PlayerSpringState(_player));
		}
	}
}
