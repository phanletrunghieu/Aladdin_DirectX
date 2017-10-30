#pragma once

#include "../Camera.h"
#include "../GameObject.h"
#include "EnemyState.h"

class Enemy : public GameObject
{
protected:
	GameObject* _target;

	int _health;
	float _speed;

	// use to detect the target being near
	int _viewRange, _attackRange;
	D3DXVECTOR2 _distanceToTarget;

	// face look right?
	bool _isRight;

	EnemyState *_state;

	//fix foot posY
	int _footPosY;
	void SetFootPosY();
public:
	Enemy();
	Enemy(GameObject * target);
	~Enemy();

	virtual void Update(float deltaTime);
	void Draw(Camera* camera);

	virtual void OnCollision(GameObject *target, GameCollision::SideCollisions side);

	bool IsTargetInViewRange();
	bool IsTargetInAttackRange();

	EnemyState* GetState();
	void SetState(EnemyState* state, bool fixFootPosition = true);

	GameObject* GetTarget();

	int GetHealth();
	void SetHealth(int newHealth);

	bool IsRight();
	void SetIsRight(bool right);

	void SetPosition(float x, float y);
	void SetPosition(D3DXVECTOR2 position);
	void SetPosition(D3DXVECTOR3 position);
};

