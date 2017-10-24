#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "../GameComponents/Graphics.h"
#include "../GameComponents/Input.h"
#include "../GameObjects/GameObject.h"

class Camera:public GameObject
{
private:
	static Camera* _instance;

	RECT _mapRect;
	GameObject* _follow;
public:
	Camera(GameObject* follow = NULL);
	~Camera();
	static Camera* GetInstance();

	void Update(float deltaTime);

	bool IsInCamera(D3DXVECTOR2 position, int width, int height);

	D3DXVECTOR2 ConvertPosition(D3DXVECTOR2 position);
	D3DXVECTOR2 ConvertPosition(float x, float y);
};