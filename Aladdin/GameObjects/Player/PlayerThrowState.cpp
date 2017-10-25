#include "PlayerThrowState.h"
#include "Player.h"

PlayerThrowState::PlayerThrowState()
{
	//not use
}

PlayerThrowState::PlayerThrowState(Player * player) : PlayerState(player, PlayerState::StateName::Throw)
{
	_animation = new Animation(ResourceManager::GetInstance()->GetAnimationXMLAladdin(), "Throw", ResourceManager::GetInstance()->GetTextureAladdin(), 0.7f);
	_animation->FlipHorizontal(!_player->IsRight());

	_animation->SetPosition(_player->GetPosition());
	_player->SetWidth(_animation->GetWidth());
	_player->SetHeight(_animation->GetHeight());

	_isCreatedAppleWeapon = false;
}


PlayerThrowState::~PlayerThrowState()
{
}

void PlayerThrowState::Update(float deltaTime)
{
	PlayerState::Update(deltaTime);

	if (!_isCreatedAppleWeapon && _animation->GetCurrentIndex() == 3)//create appleWeapon
	{
		_isCreatedAppleWeapon = true;

		AppleWeapon *appleWeapon = new AppleWeapon();
		appleWeapon->SetPosition(_player->GetPosition().x, _player->GetPosition().y);

		//set left or right for velocityX
		appleWeapon->SetVelocityX(appleWeapon->GetVelocity().x * (_player->IsRight() ? 1 : -1));

		//add gameobject to update&draw list
		SceneManager::GetInstance()->GetCurrentScene()->AddGameObjectToWeaponList(appleWeapon);

		//add appleWeapon to QuadTree
		SceneManager::GetInstance()->GetCurrentScene()->GetQuadTree()->Insert(appleWeapon);
	}

	if (_animation->IsFinish())//change state
	{
		_player->SetState(new PlayerIdleState(_player));
		return;
	}
}
