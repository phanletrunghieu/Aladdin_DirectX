#pragma once

#include "Sprite.h"
#include "QuadTree.h"
#include "../TmxParser/Tmx.h.in"
#include "../GameObjects/Camera.h"
#include "../GameObjects/Items/Apple.h"
#include "../GameObjects/Items/FloatGround.h"
#include "../GameObjects/Items/Springboard.h"
#include "../GameObjects/Player/Player.h"
#include "../GameObjects/Enemies/Enemy1/Enemy1.h"
#include "../GameObjects/Enemies/Enemy2/Enemy2.h"
#include "../GameObjects/Enemies/Enemy3/Enemy3.h"
#include "../GameObjects/Enemies/Enemy4/Enemy4.h"
#include "../GameObjects/Enemies/Enemy5/Enemy5.h"
#include "../GameObjects/Enemies/Enemy6/Enemy6.h"
#include "../GameObjects/Items/Camel.h"
#include "../GameObjects/Items/Bottle.h"
#include "../GameObjects/Items/Coal.h"
#include "../GameObjects/Enemies/BossJafar/Jafar.h"

class GameMap
{
private:
	//don't use tileset for this game
	//std::map<int, Sprite*> _listTileSet;
	Tmx::Map *_map;
	QuadTree* _quadTree;

	Player* _player;

	std::vector<Apple*> _listApples;
	std::vector<FloatGround*> _listFloatGrounds;
	std::vector<Springboard*> _listSpringboards;
	std::vector<Enemy*> _listEnemies;
	std::vector<Camel*> _listCamels;
	std::vector<Bottle*> _listBottles;
	std::vector<Coal*> _listCoal;
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

