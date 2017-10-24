#pragma once

#include "Sprite.h"
#include "QuadTree.h"
#include "../TmxParser/Tmx.h.in"
#include "../GameObjects/Camera.h"
#include "../GameObjects/Items/Apple.h"
#include "../GameObjects/Items/FloatGround.h"
#include "../GameObjects/Items/Springboard.h"

class GameMap
{
private:
	//don't use tileset for this game
	//std::map<int, Sprite*> _listTileSet;
	Tmx::Map *_map;
	QuadTree* _quadTree;

	std::vector<Apple*> _listApples;
	std::vector<FloatGround*> _listFloatGrounds;
	std::vector<Springboard*> _listSpringboards;
public:
	GameMap();
	//use QuadTree* &quadTree because quadTree is init in this function
	GameMap(char* filePath, QuadTree* &quadTree);
	~GameMap();

	void Update(float deltaTime) {};
	void Draw(Camera* camera);
	int GetWidth();
	int GetHeight();
};

