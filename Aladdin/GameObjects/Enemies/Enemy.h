#pragma once

#include "../Camera.h"
#include "../GameObject.h"
#include "EnemyState.h"

class Enemy : public GameObject
{
protected:
	int _health;

	//detect player in this range
	RECT _viewRange;

	// face look right?
	bool _isRight;

	EnemyState *_state;

	void UpdateViewRange();
public:
	Enemy();
	~Enemy();

	virtual void Update(float deltaTime);
	void Draw(Camera* camera);

	void OnCollision(GameObject *target, GameCollision::SideCollisions side);

	EnemyState* GetState();
	void SetState(EnemyState* state, bool fixFootPosition = true);

	int GetHealth();
	void SetHealth(int newHealth);

	void SetPosition(float x, float y);
	void SetPosition(D3DXVECTOR2 position);
	void SetPosition(D3DXVECTOR3 position);
	void SetPositionX(float x);
	void SetPositionY(float y);

	bool IsRight();
};

