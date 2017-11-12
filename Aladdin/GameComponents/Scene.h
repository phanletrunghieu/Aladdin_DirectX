#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "QuadTree.h"

class Scene
{
protected:
	D3DCOLOR _backgroundColor;
	QuadTree* _quadTree;

	Camera* _camera;

	/*
	list gameObject phát sinh trong game. Vd: AppleWeapon
	thêm vào list đê gọi hàm Update
	*/
	std::vector<GameObject*> _listWeapon;
public:
	Scene(D3DCOLOR backgroundColor = 0x000000);
	~Scene();

	D3DCOLOR GetBackcolor();
	QuadTree* GetQuadTree();

	Camera* GetCamera();

	void AddGameObjectToWeaponList(GameObject*gameObject);

	virtual void Update(float deltaTime);
	virtual void Draw();
	virtual void LoadContent() {};
};

