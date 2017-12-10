#pragma once

#include "../GameObject.h"
#include "../../GameComponents/Sprite.h"

class FloatGround : public GameObject
{
private:
	Sprite *_floatGroundSprite;
	D3DXVECTOR2 _firstPosition;
public:
	FloatGround();
	~FloatGround();

	void Draw(Camera* camera);

	void OnCollision(GameObject *target, GameCollision::SideCollisions side);

	void SetPosition(D3DXVECTOR2 position);
	void SetPosition(D3DXVECTOR3 position);
	void SetPosition(float x, float y);
};

