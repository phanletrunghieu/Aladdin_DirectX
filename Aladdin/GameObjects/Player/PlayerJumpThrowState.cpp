#include "PlayerJumpThrowState.h"
#include "Player.h"

PlayerJumpThrowState::PlayerJumpThrowState()
{
}

PlayerJumpThrowState::PlayerJumpThrowState(Player * player) : PlayerState(player, PlayerState::StateName::JumpThrow)
{
	_animation = new Animation(ResourceManager::GetInstance()->GetAladdinAnimationXML(), "JumpThrow", ResourceManager::GetInstance()->GetAladdinTexture(), 0.7f);
	_animation->FlipVertical(!_player->IsRight());

	_animation->SetPosition(_player->GetPosition());
	_player->SetWidth(_animation->GetWidth());
	_player->SetHeight(_animation->GetHeight());

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
