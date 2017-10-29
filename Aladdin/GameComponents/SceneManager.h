#pragma once

#include "Scene.h"

class SceneManager
{
private:
	static SceneManager *_instance;
	Scene *_currentScene;

public:
	static SceneManager *GetInstance();

	SceneManager();
	~SceneManager();

	Scene* GetCurrentScene();
	void Update(float dt);
	void ReplaceScene(Scene *scene);
};