#include "GameMap.h"

#include "../GameObjects/Items/Apple.h"
#include "../GameObjects/Items/FloatGround.h"
#include "../GameObjects/Items/Springboard.h"
#include "../GameObjects/Enemies/Enemy1/Enemy1.h"
#include "../GameObjects/Enemies/Enemy2/Enemy2.h"
#include "../GameObjects/Enemies/Enemy3/Enemy3.h"
#include "../GameObjects/Enemies/Enemy4/Enemy4.h"
#include "../GameObjects/Enemies/Enemy5/Enemy5.h"
#include "../GameObjects/Enemies/Enemy6/Enemy6.h"
#include "../GameObjects/Items/Camel.h"
#include "../GameObjects/Items/Bottle.h"
#include "../GameObjects/Items/Coal.h"
#include "../GameObjects/Items/ScoreObject/ScoreObject1.h"
#include "../GameObjects/Items/ScoreObject/ScoreObject2.h"
#include "../GameObjects/Items/Stair.h"
#include "../GameObjects/Enemies/BossJafar/Jafar.h"

GameMap::GameMap()
{}

GameMap::GameMap(char * filePath, QuadTree* &quadTree)
{
	_map = new Tmx::Map();
	_map->ParseFile(filePath);

	RECT r;
	r.left = 0;
	r.top = 0;
	r.right = this->GetWidth();
	r.bottom = this->GetHeight();
	quadTree = new QuadTree(r, 1);
	_quadTree = quadTree;

	/* don't use tileset for this game
	for (size_t i = 0; i < _map->GetNumTilesets(); i++)
	{
		const Tmx::Tileset *tileset = _map->GetTileset(i);

		std::string path = "Resources/" + tileset->GetImage()->GetSource();
		std::wstring wPath = std::wstring(path.begin(), path.end());

		_listTileSet[i] = new Sprite(wPath.c_str());
	}
	*/

	////////object here
	for (size_t i = 0; i < _map->GetNumObjectGroups(); i++)
	{
		const Tmx::ObjectGroup *objectGroup = _map->GetObjectGroup(i);

		for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
		{
			Tmx::Object *object = objectGroup->GetObjects().at(j);

			//init player
			if (objectGroup->GetName() == "Player")
			{
				_player = new Player();
				D3DXVECTOR2 pos = D3DXVECTOR2(object->GetX() + object->GetWidth() / 2, object->GetY() - object->GetHeight() / 2);
				_player->SetPosition(pos);
				_player->SetAppearPosition(pos);

				QuadTree::InsertDynamicObject(_player);
			}

			//init apple
			if (objectGroup->GetName() == "Apple")
			{
				Apple *apple = new Apple();
				apple->SetPosition(object->GetX() + object->GetWidth() / 2, object->GetY() - object->GetHeight() / 2);

				_listGameObjects.push_back(apple);

				_quadTree->InsertStaticObject(apple);
			}

			//init float ground
			if (objectGroup->GetName() == "FloatGround")
			{
				FloatGround *floatGround = new FloatGround();
				floatGround->SetPosition(object->GetX() + object->GetWidth() / 2, object->GetY() - object->GetHeight() / 2);

				_listGameObjects.push_back(floatGround);

				_quadTree->InsertStaticObject(floatGround);
			}

			//init Springboard
			if (objectGroup->GetName() == "Springboard")
			{
				Springboard *springboard = new Springboard();
				springboard->SetPosition(object->GetX() + object->GetWidth() / 2, object->GetY() - object->GetHeight() / 2);

				_listGameObjects.push_back(springboard);

				_quadTree->InsertStaticObject(springboard);
			}

			//init Enemies
			if (objectGroup->GetName() == "Enemy_1")
			{
				Enemy *enemy = new Enemy1(_player);
				enemy->SetPosition(object->GetX() + object->GetWidth() / 2, object->GetY() - object->GetHeight() / 2);

				_listGameObjects.push_back(enemy);

				QuadTree::InsertDynamicObject(enemy);
			}
			if (objectGroup->GetName() == "Enemy_2")
			{
				Enemy *enemy = new Enemy2(_player);
				enemy->SetPosition(object->GetX() + object->GetWidth() / 2, object->GetY() - object->GetHeight() / 2);

				_listGameObjects.push_back(enemy);

				QuadTree::InsertDynamicObject(enemy);
			}
			if (objectGroup->GetName() == "Enemy_3")
			{
				Enemy *enemy = new Enemy3(_player);
				enemy->SetPosition(object->GetX() + object->GetWidth() / 2, object->GetY() - object->GetHeight() / 2);

				_listGameObjects.push_back(enemy);

				QuadTree::InsertDynamicObject(enemy);
			}
			if (objectGroup->GetName() == "Enemy_4_Left")
			{
				Enemy *enemy = new Enemy4(_player);
				enemy->SetPosition(object->GetX() + object->GetWidth() / 2, object->GetY() - object->GetHeight() / 2);

				_listGameObjects.push_back(enemy);

				QuadTree::InsertDynamicObject(enemy);
			}
			if (objectGroup->GetName() == "Enemy_4_Right")
			{
				Enemy *enemy = new Enemy4(_player);
				enemy->SetPosition(object->GetX() + object->GetWidth() / 2, object->GetY() - object->GetHeight() / 2);
				enemy->SetIsRight(true);

				_listGameObjects.push_back(enemy);

				QuadTree::InsertDynamicObject(enemy);
			}
			if (objectGroup->GetName() == "Enemy_5")
			{
				Enemy *enemy = new Enemy5(_player);
				enemy->SetPosition(object->GetX() + object->GetWidth() / 2, object->GetY() - object->GetHeight() / 2);

				_listGameObjects.push_back(enemy);

				QuadTree::InsertDynamicObject(enemy);
			}
			if (objectGroup->GetName() == "Enemy_6")
			{
				Enemy *enemy = new Enemy6(_player);
				enemy->SetPosition(object->GetX() + object->GetWidth() / 2, object->GetY() - object->GetHeight() / 2);
				enemy->SetIsRight(true);

				_listGameObjects.push_back(enemy);

				_quadTree->InsertStaticObject(enemy);
			}

			//score object
			if (objectGroup->GetName() == "ScoreObject1")
			{
				ScoreObject1 *obj = new ScoreObject1();
				obj->SetPosition(object->GetX() + object->GetWidth() / 2, object->GetY() - object->GetHeight() / 2);

				_listGameObjects.push_back(obj);

				_quadTree->InsertStaticObject(obj);
			}
			if (objectGroup->GetName() == "ScoreObject2")
			{
				ScoreObject2 *obj = new ScoreObject2();
				obj->SetPosition(object->GetX() + object->GetWidth() / 2, object->GetY() - object->GetHeight() / 2);

				_listGameObjects.push_back(obj);

				_quadTree->InsertStaticObject(obj);
			}

			//init BossJafar
			if (objectGroup->GetName() == "Jafar")
			{
				Jafar* jaFar = new Jafar(_player);
				jaFar->SetPosition(object->GetX() + object->GetWidth() / 2, object->GetY() - object->GetHeight() / 2);

				_listGameObjects.push_back(jaFar);

				_quadTree->InsertStaticObject(jaFar);
			}

			//camel
			if (objectGroup->GetName() == "Camel")
			{
				Camel *camel = new Camel();
				camel->SetPosition(object->GetX() + object->GetWidth() / 2, object->GetY() - object->GetHeight() / 2);

				_listGameObjects.push_back(camel);

				_quadTree->InsertStaticObject(camel);
			}

			//bottle
			if (objectGroup->GetName() == "Bottle")
			{
				Bottle *bottle = new Bottle();
				bottle->SetPosition(object->GetX() + object->GetWidth() / 2, object->GetY() - object->GetHeight() / 2);

				_listGameObjects.push_back(bottle);

				_quadTree->InsertStaticObject(bottle);
			}

			//init coal
			if (objectGroup->GetName() == "Coal")
			{
				Coal *coal = new Coal();
				coal->SetPosition(object->GetX() + object->GetWidth() / 2, object->GetY() + object->GetHeight() / 2);
				coal->SetWidth(object->GetWidth());
				coal->SetHeight(object->GetHeight());

				_listGameObjects.push_back(coal);

				_quadTree->InsertStaticObject(coal);
			}

			//init ground
			if (objectGroup->GetName() == "Ground")
			{
				GameObject *gameObject = new GameObject(GameObject::GameObjectType::Ground);
				gameObject->SetPosition(object->GetX() + object->GetWidth() / 2, object->GetY() + object->GetHeight() / 2);
				gameObject->SetWidth(object->GetWidth());
				gameObject->SetHeight(object->GetHeight());

				_quadTree->InsertStaticObject(gameObject);
			}

			//init stair
			if (objectGroup->GetName() == "Stair_Right")
			{
				Stair *gameObject = new Stair(GameCollision::SideCollisions::Right);
				gameObject->SetPosition(object->GetX() + object->GetWidth() / 2, object->GetY() + object->GetHeight() / 2);
				gameObject->SetWidth(object->GetWidth());
				gameObject->SetHeight(object->GetHeight());

				_listGameObjects.push_back(gameObject);

				_quadTree->InsertStaticObject(gameObject);
			}

			//init wall
			if (objectGroup->GetName() == "Wall")
			{
				GameObject *gameObject = new GameObject(GameObject::GameObjectType::Wall);
				gameObject->SetPosition(object->GetX() + object->GetWidth() / 2, object->GetY() + object->GetHeight() / 2);
				gameObject->SetWidth(object->GetWidth());
				gameObject->SetHeight(object->GetHeight());

				_quadTree->InsertStaticObject(gameObject);
			}

			//init colbany
			if (objectGroup->GetName() == "Colbany")
			{
				GameObject *gameObject = new GameObject(GameObject::GameObjectType::Colbany);
				gameObject->SetPosition(object->GetX() + object->GetWidth() / 2, object->GetY() + object->GetHeight() / 2);
				gameObject->SetWidth(object->GetWidth());
				gameObject->SetHeight(object->GetHeight());

				_quadTree->InsertStaticObject(gameObject);
			}

			//init ToJafarSence
			if (objectGroup->GetName() == "ToJafarScene")
			{
				GameObject *gameObject = new GameObject(GameObject::GameObjectType::ToJafarScene);
				gameObject->SetPosition(object->GetX() + object->GetWidth() / 2, object->GetY() + object->GetHeight() / 2);
				gameObject->SetWidth(object->GetWidth());
				gameObject->SetHeight(object->GetHeight());

				_quadTree->InsertStaticObject(gameObject);
			}

			//init rope
			if (objectGroup->GetName() == "Rope")
			{
				GameObject *gameObject = new GameObject(GameObject::GameObjectType::Rope);
				gameObject->SetPosition(object->GetX() + object->GetWidth() / 2, object->GetY() + object->GetHeight() / 2);
				gameObject->SetWidth(object->GetWidth());
				gameObject->SetHeight(object->GetHeight());

				_quadTree->InsertStaticObject(gameObject);
			}

			//init HorizontalBar
			if (objectGroup->GetName() == "HorizontalBar")
			{
				GameObject *gameObject = new GameObject(GameObject::GameObjectType::HorizontalBar);
				gameObject->SetPosition(object->GetX() + object->GetWidth() / 2, object->GetY() + object->GetHeight() / 2);
				gameObject->SetWidth(object->GetWidth());
				gameObject->SetHeight(object->GetHeight());

				_quadTree->InsertStaticObject(gameObject);
			}
		}
	}
}

GameMap::~GameMap()
{
	delete _map;
	_map = 0;

	delete _player;
	_player = 0;

	_quadTree->Clear();
	delete _quadTree;
	_quadTree = 0;

	for (size_t i = 0; i < _listGameObjects.size(); i++)
	{
		if (_listGameObjects[i])
			delete _listGameObjects[i];
	}
	_listGameObjects.clear();

	/*don't use tileset for this game
	for (size_t i = 0; i < _listTileSet.size(); i++)
	{
		if (_listTileSet[i])
			delete _listTileSet[i];
	}
	_listTileSet.clear();
	*/
}

void GameMap::Update(float deltaTime)
{
	//player
	_player->Update(deltaTime);

	for (size_t i = 0; i < _listGameObjects.size(); i++)
		_listGameObjects[i]->Update(deltaTime);
}

void GameMap::Draw(Camera * camera)
{
	/*don't use tileset for this game
	for (size_t i = 0; i < _map->GetNumTileLayers(); i++)
	{
		const Tmx::TileLayer *layer = _map->GetTileLayer(i);

		if (!layer->IsVisible())
		{
			continue;
		}

		for (size_t m = 0; m < layer->GetWidth(); m++)
		{
			for (size_t n = 0; n < layer->GetHeight(); n++)
			{
				int tilesetIndex = layer->GetTileTilesetIndex(m, n);
				if (tilesetIndex != -1)
				{
					const Tmx::Tileset *tileSet = _map->GetTileset(tilesetIndex);
					int tileWidth = _map->GetTileWidth();
					int tileHeight = _map->GetTileHeight();

					int tileSetWidth = tileSet->GetImage()->GetWidth() / tileWidth;
					int tileSetHeight = tileSet->GetImage()->GetHeight() / tileHeight;


					int tileID = layer->GetTileId(m, n);

					int y = tileID / tileSetWidth;
					int x = tileID - y * tileSetWidth;

					RECT sourceRECT;
					sourceRECT.top = y * tileHeight;
					sourceRECT.bottom = sourceRECT.top + tileHeight;
					sourceRECT.left = x * tileWidth;
					sourceRECT.right = sourceRECT.left + tileWidth;

					Sprite* sprite = _listTileSet[tilesetIndex];

					D3DXVECTOR3 position(m * tileWidth + tileWidth / 2, n * tileHeight + tileHeight / 2, 0);
					sprite->SetPosition(position);

					sprite->SetWidth(tileWidth);
					sprite->SetHeight(tileHeight);

					sprite->SetSourceRect(sourceRECT);
					sprite->Draw(camera);
				}
			}
		}
	}
	*/

	//////draw object here
	for (size_t i = 0; i < _listGameObjects.size(); i++)
	{
		//remove not visible object
		if (!_listGameObjects[i]->IsVisible())
		{
			_quadTree->RemoveStaticObject(_listGameObjects[i]);
			_listGameObjects.erase(_listGameObjects.begin() + i);
			i--;
			continue;
		}

		//visible -> draw
		_listGameObjects[i]->Draw(camera);
	}

	//player
	_player->Draw(camera);
}

Player * GameMap::GetPlayer()
{
	return _player;
}

int GameMap::GetWidth()
{
	return _map->GetWidth() * _map->GetTileWidth();
}

int GameMap::GetHeight()
{
	return _map->GetHeight() * _map->GetTileHeight();
}