#pragma once

#include "../../GameComponents/Animation.h"

class Player;

class PlayerState
{
public:
	enum StateName
	{
		Idle,
		Run,
		Stop,//run->idle
		CrouchIdle,
		CrouchAttack,
		Fall,
		Jump,
		Attack,
		Throw,
		JumpAttack,
		JumpThrow,
		RunJump,
		RunFall,
		Spring,//nhay cuon tron
		ClimbVertical,
		ClimbAttack,
		ClimbVerticalJump,
		ClimbVerticalFall,
		ClimbHorizontalIde,
		ClimbHorizontalMove,
		Damage,
		Death
	};
protected:
	StateName _name;

	Player *_player;
	Animation *_animation;

	//special for attack state (used to make sure that player is attacked once at each attackState)
	bool _isAttackedEnemy;
public:
	PlayerState();
	PlayerState(Player *player, StateName name = StateName::Idle);
	~PlayerState();

	virtual void Update(float deltaTime);
	virtual void OnCollision(GameObject *target, GameCollision::SideCollisions side) {};

	Animation* GetAnimation();
	void SetAnimation(Animation* newAnimation);

	StateName GetName();

	//special for attack state (used to make sure that player is attacked once at each attackState)
	bool IsAttackedEnemy();
	void SetIsAttackedEnemy(bool value);
};

