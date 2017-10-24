#pragma once

#include "../GameObjects/Camera.h"
#include "../GameComponents/Sprite.h"
#include "../GameComponents/Scene.h"
#include "../GameComponents/Input.h"
#include "../GameComponents/GameMap.h"
#include "../GameObjects/Player/Player.h"


class MainScene : public Scene
{
private:
	std::vector<Sprite*> _backgroundTextures;
	GameMap* _gameMap;
	Player* _player;

	void CheckCollision();
public:
	MainScene();
	~MainScene();

	void LoadContent();
	void Update(float dt);
	void Draw();
};

