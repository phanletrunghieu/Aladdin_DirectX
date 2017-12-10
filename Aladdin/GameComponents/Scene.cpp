#include "Scene.h"

Scene::Scene(D3DCOLOR backgroundColor)
{
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
	_gameMap->Update(deltaTime);
	if((int)_camera != 0xDDDDDDDD)
		_camera->Update(deltaTime);

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
	_gameMap->Draw(_camera);

	for (size_t i = 0; i < _listWeapon.size(); i++)
	{
		_listWeapon[i]->Draw(_camera);
	}
}
