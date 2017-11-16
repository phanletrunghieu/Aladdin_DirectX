#include "GameMap.h"

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
				_player->SetPosition(object->GetX() + object->GetWidth() / 2, object->GetY() - object->GetHeight() / 2);

				QuadTree::InsertDynamicObject(_player);
			}

			//init apple
			if (objectGroup->GetName() == "Apple")
			{
				Apple *apple = new Apple();
				apple->SetPosition(object->GetX() + object->GetWidth() / 2, object->GetY() - object->GetHeight() / 2);

				_listApples.push_back(apple);

				_quadTree->InsertStaticObject(apple);
			}

			//init float ground
			if (objectGroup->GetName() == "FloatGround")
			{
				FloatGround *floatGround = new FloatGround();
				floatGround->SetPosition(object->GetX() + object->GetWidth() / 2, object->GetY() - object->GetHeight() / 2);

				_listFloatGrounds.push_back(floatGround);

				_quadTree->InsertStaticObject(floatGround);
			}

			//init Springboard
			if (objectGroup->GetName() == "Springboard")
			{
				Springboard *springboard = new Springboard();
				springboard->SetPosition(object->GetX() + object->GetWidth() / 2, object->GetY() - object->GetHeight() / 2);

				_listSpringboards.push_back(springboard);

				_quadTree->InsertStaticObject(springboard);
			}

			//init Enemies
			if (objectGroup->GetName() == "Enemy_1")
			{
				Enemy *enemy = new Enemy1(_player);
				enemy->SetPosition(object->GetX() + object->GetWidth() / 2, object->GetY() - object->GetHeight() / 2);

				_listEnemies.push_back(enemy);

				QuadTree::InsertDynamicObject(enemy);
			}
			if (objectGroup->GetName() == "Enemy_2")
			{
				Enemy *enemy = new Enemy2(_player);
				enemy->SetPosition(object->GetX() + object->GetWidth() / 2, object->GetY() - object->GetHeight() / 2);

				_listEnemies.push_back(enemy);

				QuadTree::InsertDynamicObject(enemy);
			}
			if (objectGroup->GetName() == "Enemy_3")
			{
				Enemy *enemy = new Enemy3(_player);
				enemy->SetPosition(object->GetX() + object->GetWidth() / 2, object->GetY() - object->GetHeight() / 2);

				_listEnemies.push_back(enemy);

				QuadTree::InsertDynamicObject(enemy);
			}
			if (objectGroup->GetName() == "Enemy_4_Left")
			{
				Enemy *enemy = new Enemy4(_player);
				enemy->SetPosition(object->GetX() + object->GetWidth() / 2, object->GetY() - object->GetHeight() / 2);
				enemy->AllowMoveLeft(false);
				enemy->AllowMoveRight(false);

				_listEnemies.push_back(enemy);

				QuadTree::InsertDynamicObject(enemy);
			}
			if (objectGroup->GetName() == "Enemy_4_Right")
			{
				Enemy *enemy = new Enemy4(_player);
				enemy->SetPosition(object->GetX() + object->GetWidth() / 2, object->GetY() - object->GetHeight() / 2);
				enemy->SetIsRight(true);
				enemy->AllowMoveLeft(false);
				enemy->AllowMoveRight(false);

				_listEnemies.push_back(enemy);

				QuadTree::InsertDynamicObject(enemy);
			}
			if (objectGroup->GetName() == "Enemy_5")
			{
				Enemy *enemy = new Enemy5(_player);
				enemy->SetPosition(object->GetX() + object->GetWidth() / 2, object->GetY() - object->GetHeight() / 2);

				_listEnemies.push_back(enemy);

				QuadTree::InsertDynamicObject(enemy);
			}

			//camel
			if (objectGroup->GetName() == "Camel")
			{
				Camel *camel = new Camel();
				camel->SetPosition(object->GetX() + object->GetWidth() / 2, object->GetY() - object->GetHeight() / 2);

				_listCamels.push_back(camel);

				_quadTree->InsertStaticObject(camel);
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

			//init wall
			if (objectGroup->GetName() == "Wall")
			{
				GameObject *gameObject = new GameObject(GameObject::GameObjectType::Wall);
				gameObject->SetPosition(object->GetX() + object->GetWidth() / 2, object->GetY() + object->GetHeight() / 2);
				gameObject->SetWidth(object->GetWidth());
				gameObject->SetHeight(object->GetHeight());

				_quadTree->InsertStaticObject(gameObject);
			}

			//init coal
			if (objectGroup->GetName() == "Coal")
			{
				GameObject *gameObject = new GameObject(GameObject::GameObjectType::Coal);
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
	delete _player;

	_quadTree->Clear();
	delete _quadTree;

	for (size_t i = 0; i < _listApples.size(); i++)
	{
		if (_listApples[i])
			delete _listApples[i];
	}
	_listApples.clear();

	for (size_t i = 0; i < _listFloatGrounds.size(); i++)
	{
		if (_listFloatGrounds[i])
			delete _listFloatGrounds[i];
	}
	_listFloatGrounds.clear();

	for (size_t i = 0; i < _listSpringboards.size(); i++)
	{
		if (_listSpringboards[i])
			delete _listSpringboards[i];
	}
	_listSpringboards.clear();

	for (size_t i = 0; i < _listEnemies.size(); i++)
	{
		if (_listEnemies[i])
			delete _listEnemies[i];
	}
	_listEnemies.clear();

	for (size_t i = 0; i < _listCamels.size(); i++)
	{
		if (_listCamels[i])
			delete _listCamels[i];
	}
	_listCamels.clear();

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
	//apple
	for (size_t i = 0; i < _listApples.size(); i++)
		_listApples[i]->Update(deltaTime);

	//float ground
	for (size_t i = 0; i < _listFloatGrounds.size(); i++)
		_listFloatGrounds[i]->Update(deltaTime);

	//springboard
	for (size_t i = 0; i < _listSpringboards.size(); i++)
		_listSpringboards[i]->Update(deltaTime);

	//enemies
	for (size_t i = 0; i < _listEnemies.size(); i++)
		_listEnemies[i]->Update(deltaTime);

	//camels
	for (size_t i = 0; i < _listCamels.size(); i++)
		_listCamels[i]->Update(deltaTime);

	//player
	_player->Update(deltaTime);
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
	//apple
	for (size_t i = 0; i < _listApples.size(); i++)
	{
		//remove not visible object
		if (!_listApples[i]->IsVisible())
		{
			_quadTree->RemoveStaticObject(_listApples[i]);
			_listApples.erase(_listApples.begin() + i);
			i--;
			continue;
		}

		//visible -> draw
		_listApples[i]->Draw(camera);
	}

	//float ground
	for (size_t i = 0; i < _listFloatGrounds.size(); i++)
	{
		//remove not visible object
		if (!_listFloatGrounds[i]->IsVisible())
		{
			_quadTree->RemoveStaticObject(_listFloatGrounds[i]);
			_listFloatGrounds.erase(_listFloatGrounds.begin() + i);
			i--;
			continue;
		}

		//visible -> draw
		_listFloatGrounds[i]->Draw(camera);
	}

	//springboard
	for (size_t i = 0; i < _listSpringboards.size(); i++)
	{
		_listSpringboards[i]->Draw(camera);
	}

	//enemies
	for (size_t i = 0; i < _listEnemies.size(); i++)
	{
		//remove not visible object
		if (!_listEnemies[i]->IsVisible())
		{
			QuadTree::RemoveDynamicObject(_listEnemies[i]);
			_listEnemies.erase(_listEnemies.begin() + i);
			i--;
			continue;
		}

		//visible -> draw
		_listEnemies[i]->Draw(camera);
	}

	//camels
	for (size_t i = 0; i < _listCamels.size(); i++)
	{
		//remove not visible object
		if (!_listCamels[i]->IsVisible())
		{
			_quadTree->RemoveStaticObject(_listCamels[i]);
			_listCamels.erase(_listCamels.begin() + i);
			i--;
			continue;
		}

		//visible -> draw
		_listCamels[i]->Draw(camera);
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