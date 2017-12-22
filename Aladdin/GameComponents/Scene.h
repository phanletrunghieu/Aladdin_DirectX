#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "QuadTree.h"
#include "GameMap.h"

class Scene
{
protected:
	D3DCOLOR _backgroundColor;
	QuadTree* _quadTree;

	Camera* _camera;
	GameMap* _gameMap;

	/*
	list gameObject phát sinh trong game. Vd: AppleWeapon
	thêm vào list đê gọi hàm Update
	*/
	std::vector<GameObject*> _listWeapon;
public:
	enum SceneName
	{
		MainScenes,
		JafarScenes,
		VictoryScenes,
		DefeatScenes
	};

	SceneName _sceneName;

	Scene(SceneName sceneName, D3DCOLOR backgroundColor = 0x000000);
	virtual ~Scene();

	SceneName GetSceneName();

	D3DCOLOR GetBackcolor();
	QuadTree* GetQuadTree();

	Camera* GetCamera();
	void SetCamera(Camera* camera);

	GameMap* GetGameMap();

	void AddGameObjectToWeaponList(GameObject*gameObject);

	virtual void Update(float deltaTime);
	virtual void Draw();
	virtual void LoadContent() {};
};

