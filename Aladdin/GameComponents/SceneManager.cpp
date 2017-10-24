#include "SceneManager.h"

SceneManager* SceneManager::_instance = NULL;

SceneManager::SceneManager()
{
	_currentScene = NULL;
}

SceneManager::~SceneManager()
{
}

SceneManager* SceneManager::GetInstance()
{
	if (!_instance)
		_instance = new SceneManager();

	return _instance;
}

Scene* SceneManager::GetCurrentScene()
{
	return _currentScene;
}

void SceneManager::Update(float dt)
{
	_currentScene->Update(dt);
}

void SceneManager::ReplaceScene(Scene *scene)
{
	delete _currentScene;

	_currentScene = scene;
}