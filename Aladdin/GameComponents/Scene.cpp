#include "Scene.h"

Scene::Scene(D3DCOLOR backgroundColor)
{
	this->_backgroundColor = backgroundColor;
	LoadContent();
}

Scene::~Scene()
{
}

D3DCOLOR Scene::GetBackcolor()
{
	return _backgroundColor;
}

QuadTree * Scene::GetQuadTree()
{
	return _quadTree;
}

void Scene::AddGameObjectToWeaponList(GameObject * gameObject)
{
	_listWeapon.push_back(gameObject);
}

void Scene::Update(float deltaTime)
{
	for (size_t i = 0; i < _listWeapon.size(); i++)
	{
		if (!_listWeapon[i]->IsVisible())
		{
			delete _listWeapon[i];
			_listWeapon.erase(_listWeapon.begin() + i);
			continue;
		}
		_listWeapon[i]->Update(deltaTime);
	}
}

void Scene::Draw()
{
	for (size_t i = 0; i < _listWeapon.size(); i++)
	{
		_listWeapon[i]->Draw(_camera);
	}
}
