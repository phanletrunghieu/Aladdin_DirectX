#pragma once

#include "Sprite.h"
#include "QuadTree.h"
#include "../TmxParser/Tmx.h.in"
#include "../GameObjects/Camera.h"
#include "../GameObjects/Player/Player.h"

class GameMap
{
private:
	//don't use tileset for this game
	//std::map<int, Sprite*> _listTileSet;
	Tmx::Map *_map;
	QuadTree* _quadTree;

	Player* _player;

	std::vector<GameObject*> _listGameObjects;
public:
	GameMap();
	//use QuadTree* &quadTree because quadTree is init in this function
	GameMap(char* filePath, QuadTree* &quadTree);
	~GameMap();

	void Update(float deltaTime);
	void Draw(Camera* camera);

	Player* GetPlayer();

	int GetWidth();
	int GetHeight();
};

