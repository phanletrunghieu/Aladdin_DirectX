#include "PlayerThrowState.h"
#include "Player.h"
#include "PlayerIdleState.h"
#include "../Weapons/PlayerWeapons/AppleWeapon.h"
#include "../../GameComponents/SceneManager.h"

PlayerThrowState::PlayerThrowState()
{
	//not use
}

PlayerThrowState::PlayerThrowState(Player * player) : PlayerState(player, PlayerState::StateName::Throw)
{
	SetAnimation(new Animation(ResourceManager::GetInstance()->GetAnimationXMLAladdin(), "Throw", ResourceManager::GetInstance()->GetTextureAladdin(), true, 0.4f));

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
		_player->SetNumAppleWeapon(_player->GetNumAppleWeapon() - 1);

		AppleWeapon *appleWeapon = new AppleWeapon();
		appleWeapon->SetPosition(_player->GetPosition().x, _player->GetPosition().y);

		//set left or right for velocityX
		appleWeapon->SetVelocityX(appleWeapon->GetVelocity().x * (_player->IsRight() ? 1 : -1));

		//add gameobject to update&draw list
		SceneManager::GetInstance()->GetCurrentScene()->AddGameObjectToWeaponList(appleWeapon);

		//add appleWeapon to QuadTree
		QuadTree::InsertDynamicObject(appleWeapon);
	}

	if (_animation->IsFinish())//change state
	{
		_player->SetState(new PlayerIdleState(_player));
		return;
	}
}
