#pragma once

#include "../../GameComponents/Animation.h"

class Enemy;

class EnemyState
{
public:
	enum StateName
	{
		Idle, Walk, Attack, Damage, Jafar, Snake
	};
	EnemyState();
	EnemyState(Enemy *enemy, StateName name = StateName::Idle);
	virtual ~EnemyState();

	virtual void Update(float deltaTime);
	virtual void OnCollision(GameObject *target, GameCollision::SideCollisions side) {};

	Animation* GetAnimation();
	void SetAnimation(Animation* newAnimation);

	StateName GetName();

	//special for attack state (used to make sure that player is attacked once at each attackState)
	bool IsAttackedPlayer();
	void SetIsAttackedPlayer(bool value);

protected:
	StateName _name;
	Enemy* _enemy;
	Animation* _animation;

	float _totalDuration;

	//special for attack state (used to make sure that player is attacked once at each attackState)
	bool _isAttackedPlayer;
};

