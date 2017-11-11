#include "PlayerState.h"
#include "Player.h"

PlayerState::PlayerState()
{
}

PlayerState::PlayerState(Player *player, StateName name)
{
	_name = name;
	_player = player;

	//special for attack state
	_isAttackedEnemy = false;
}

PlayerState::~PlayerState()
{
	if (_animation)
	{
		delete _animation;
		_animation = NULL;
	}
}

void PlayerState::Update(float deltaTime)
{
	if (_animation != NULL)
	{
		_animation->SetPosition(_player->GetPosition());
		_animation->FlipHorizontal(!_player->IsRight());

		_animation->Update(deltaTime);//after animation update, animation's position maybe change
		_player->SetPosition(_animation->GetPosition());
	}

	_player->SetWidth(_animation->GetWidth());
	_player->SetHeight(_animation->GetHeight());

	//reset "_isAttackedPlayer"
	if (_animation->IsBegin())
		_isAttackedEnemy = false;
}

Animation * PlayerState::GetAnimation()
{
	return _animation;
}

void PlayerState::SetAnimation(Animation * newAnimation)
{
	_animation = newAnimation;

	_animation->FlipHorizontal(!_player->IsRight());
	_animation->SetPosition(_player->GetPosition());
	_player->SetWidth(_animation->GetWidth());
	_player->SetHeight(_animation->GetHeight());
}

PlayerState::StateName PlayerState::GetName()
{
	return _name;
}

bool PlayerState::IsAttackedEnemy()
{
	return _isAttackedEnemy;
}

void PlayerState::SetIsAttackedEnemy(bool value)
{
	_isAttackedEnemy = value;
}
