#include "Scene.h"

Scene::Scene(SceneName sceneName, D3DCOLOR backgroundColor)
{
	this->_sceneName = sceneName;
	this->_backgroundColor = backgroundColor;
	LoadContent();
}

Scene::~Scene()
{
	if (_camera)
	{
		delete _camera;
		_camera = NULL;
	}

	if (_gameMap)
	{
		delete _gameMap;
		_gameMap = NULL;
	}
}

Scene::SceneName Scene::GetSceneName()
{
	return _sceneName;
}

D3DCOLOR Scene::GetBackcolor()
{
	return _backgroundColor;
}

QuadTree * Scene::GetQuadTree()
{
	return _quadTree;
}

Camera * Scene::GetCamera()
{
	return _camera;
}

void Scene::SetCamera(Camera * camera)
{
	_camera = camera;
}

GameMap * Scene::GetGameMap()
{
	return _gameMap;
}

void Scene::AddGameObjectToWeaponList(GameObject * gameObject)
{
	_listWeapon.push_back(gameObject);
}

void Scene::Update(float deltaTime)
{
	_camera->Update(deltaTime);
	_gameMap->Update(deltaTime);

	for (size_t i = 0; i < _listWeapon.size(); i++)
	{
		if (!_listWeapon[i]->IsVisible())
		{
			QuadTree::RemoveDynamicObject(_listWeapon[i]);
			_listWeapon.erase(_listWeapon.begin() + i);
			continue;
		}
		_listWeapon[i]->Update(deltaTime);
	}
}

void Scene::Draw()
{
	if (_gameMap != NULL)
		_gameMap->Draw(_camera);

	for (size_t i = 0; i < _listWeapon.size(); i++)
	{
		_listWeapon[i]->Draw(_camera);
	}
}
