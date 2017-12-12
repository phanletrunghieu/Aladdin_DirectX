#pragma once

#include "../Camera.h"
#include "../GameObject.h"
#include "PlayerState.h"

class Player:public GameObject
{
private:
	static int _timesPlay;//luot choi
	static int _score;

	D3DXVECTOR2 _appearPosition;

	PlayerState *_state;
	bool _isRight, _isGround, _allowMoveLeft, _allowMoveRight;
	float _speed, _jumpForce, _jumpRunForce;

	//when colliding with coal, each duration, player's health will decrease
	float _collidedWithCoalDuration;

	int _health, _damage, _numAppleWeapon;
public:
	static int GetTimesPlay();
	static int GetScore();
	Player();
	~Player();

	//use when died
	void Reset();

	void Update(float deltaTime);
	void Draw(Camera* camera);

	void CheckCollision();
	void OnCollision(GameObject *target, GameCollision::SideCollisions side);

	PlayerState* GetState();
	void SetState(PlayerState* state, bool fixFootPosition = true);

	bool IsRight();
	bool IsGround();
	void SetIsGround(bool isGround);

	bool IsAllowMoveLeft();
	bool IsAllowMoveRight();
	void AllowMoveLeft(bool allow);
	void AllowMoveRight(bool allow);

	D3DXVECTOR2 GetAppearPosition();
	void SetAppearPosition(D3DXVECTOR2 appearPositioin);

	float GetSpeed();
	void SetSpeed(float speed);

	float GetJumpForce();
	void SetJumpForce(float force);

	float GetJumpRunForce();
	void SetJumpRunForce(float force);

	int GetHealth();
	void SetHealth(int newHealth);

	int GetDamage();
	void SetDamage(int newDamage);

	int GetNumAppleWeapon();
	void SetNumAppleWeapon(int value);
};

