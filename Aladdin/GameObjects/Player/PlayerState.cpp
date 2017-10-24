#include "PlayerState.h"
#include "Player.h"

PlayerState::PlayerState()
{
}

PlayerState::PlayerState(Player *player, StateName name)
{
	_name = name;
	_player = player;
}

PlayerState::~PlayerState()
{
	delete _animation;
}

void PlayerState::Update(float deltaTime)
{
	if (_animation != NULL)
		_animation->Update(deltaTime);

	_animation->SetPosition(_player->GetPosition());
	_animation->FlipVertical(!_player->IsRight());
}

Animation * PlayerState::GetAnimation()
{
	return _animation;
}

PlayerState::StateName PlayerState::GetName()
{
	return _name;
}
