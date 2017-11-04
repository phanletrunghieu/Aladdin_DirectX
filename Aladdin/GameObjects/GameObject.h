#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "../GameComponents/Input.h"
#include "../GameComponents/GameCollision.h"
#include "../GameComponents/ResourceManager.h"

class Camera;

class GameObject
{
public:
	enum GameObjectType
	{
		None, Player, Enemies, Apple, AppleWeapon, Ground, Rope, HorizontalBar, FloatGround, Springboard
	};
protected:
	GameObjectType _tag;
	D3DXVECTOR2 _position;
	D3DXVECTOR2 _velocity;
	D3DXVECTOR2 _acceleration;
	float _mass;//khoi luong
	int _width, _height;

	bool _isVisible;

	Input* _input;
public:
	GameObject(GameObjectType tag = None);
	~GameObject();

	virtual void Draw(Camera *camera) {}
	virtual void Update(float deltaTime);

	virtual void OnCollision(GameObject *target, GameCollision::SideCollisions side) {};

	//Getter, setter
	GameObject::GameObjectType GetTag();

	bool IsVisible();

	D3DXVECTOR2 GetPosition();
	virtual void SetPosition(float x, float y);
	virtual void SetPosition(D3DXVECTOR2 position);
	virtual void SetPosition(D3DXVECTOR3 position);
	virtual void SetPositionX(float x);
	virtual void SetPositionY(float y);

	D3DXVECTOR2 GetVelocity();
	virtual void SetVelocity(float x, float y);
	virtual void SetVelocityX(float x);
	virtual void SetVelocityY(float y);

	D3DXVECTOR2 GetAcceleration();
	virtual void SetAcceleration(float x, float y);
	virtual void SetAccelerationX(float x);
	virtual void SetAccelerationY(float y);

	float GetMass();
	virtual void SetMass(float mass);

	int GetWidth();
	virtual void SetWidth(int width);

	int GetHeight();
	virtual void SetHeight(int height);

	void GetBound(float &top, float &right, float &bottom, float &left);
	RECT GetBound();
};

