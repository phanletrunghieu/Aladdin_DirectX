#pragma once

#include "../GameObjects/Camera.h"
#include "../GameComponents/Sprite.h"
#include "../GameComponents/Scene.h"
#include "../GameComponents/Input.h"
#include "../GameComponents/GameMap.h"


class MainScene : public Scene
{
private:
	std::vector<Sprite*> _backgroundTextures;
	GameMap* _gameMap;

	void CheckCollision();
public:
	MainScene();
	~MainScene();

	void LoadContent();
	void Update(float dt);
	void Draw();
};

