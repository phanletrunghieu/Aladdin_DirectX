#include "PlayerJumpThrowState.h"
#include "Player.h"
#include "PlayerJumpState.h"
#include "PlayerFallState.h"
#include "PlayerRunJumpState.h"
#include "PlayerRunFallState.h"
#include "../Weapons/PlayerWeapons/AppleWeapon.h"
#include "../../GameComponents/SceneManager.h"

PlayerJumpThrowState::PlayerJumpThrowState()
{
}

PlayerJumpThrowState::PlayerJumpThrowState(Player * player) : PlayerState(player, PlayerState::StateName::JumpThrow)
{
	SetAnimation(new Animation(ResourceManager::GetInstance()->GetAnimationXMLAladdin(), "JumpThrow", ResourceManager::GetInstance()->GetTextureAladdin(), true, 0.4f));

	_isCreatedAppleWeapon = false;
}


PlayerJumpThrowState::~PlayerJumpThrowState()
{
}

void PlayerJumpThrowState::Update(float deltaTime)
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
		D3DXVECTOR2 playerVelocity = _player->GetVelocity();
		if (playerVelocity.x == 0)
		{
			if (playerVelocity.y < 0)
			{
				_player->SetState(new PlayerJumpState(_player));
			}
			else
			{
				_player->SetState(new PlayerFallState(_player));
			}
		}
		else
		{
			if (playerVelocity.y < 0)
			{
				_player->SetState(new PlayerRunJumpState(_player));
			}
			else
			{
				_player->SetState(new PlayerRunFallState(_player));
			}
		}
	}
}
