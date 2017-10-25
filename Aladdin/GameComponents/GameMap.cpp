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

			//init apple
			if (objectGroup->GetName() == "Apple")
			{
				Apple *apple = new Apple();
				apple->SetPosition(object->GetX() + object->GetWidth() / 2, object->GetY() - object->GetHeight() / 2);
				apple->SetWidth(object->GetWidth());
				apple->SetHeight(object->GetHeight());

				_listApples.push_back(apple);

				_quadTree->Insert(apple);
			}

			//init float ground
			if (objectGroup->GetName() == "FloatGround")
			{
				FloatGround *floatGround = new FloatGround();
				floatGround->SetPosition(object->GetX() + object->GetWidth() / 2, object->GetY() - object->GetHeight() / 2);
				floatGround->SetWidth(object->GetWidth());
				floatGround->SetHeight(object->GetHeight());

				_listFloatGrounds.push_back(floatGround);

				_quadTree->Insert(floatGround);
			}

			//init Springboard
			if (objectGroup->GetName() == "Springboard")
			{
				Springboard *springboard = new Springboard();
				springboard->SetPosition(object->GetX() + object->GetWidth() / 2, object->GetY() - object->GetHeight() / 2);
				springboard->SetWidth(object->GetWidth());
				springboard->SetHeight(object->GetHeight());

				_listSpringboards.push_back(springboard);

				_quadTree->Insert(springboard);
			}

			//init ground
			if (objectGroup->GetName() == "Ground")
			{
				GameObject *gameObject = new GameObject(GameObject::GameObjectType::Ground);
				gameObject->SetPosition(object->GetX() + object->GetWidth() / 2, object->GetY() + object->GetHeight() / 2);
				gameObject->SetWidth(object->GetWidth());
				gameObject->SetHeight(object->GetHeight());

				_quadTree->Insert(gameObject);
			}

			//init rope
			if (objectGroup->GetName() == "Rope")
			{
				GameObject *gameObject = new GameObject(GameObject::GameObjectType::Rope);
				gameObject->SetPosition(object->GetX() + object->GetWidth() / 2, object->GetY() + object->GetHeight() / 2);
				gameObject->SetWidth(object->GetWidth());
				gameObject->SetHeight(object->GetHeight());

				_quadTree->Insert(gameObject);
			}

			//init HorizontalBar
			if (objectGroup->GetName() == "HorizontalBar")
			{
				GameObject *gameObject = new GameObject(GameObject::GameObjectType::HorizontalBar);
				gameObject->SetPosition(object->GetX() + object->GetWidth() / 2, object->GetY() + object->GetHeight() / 2);
				gameObject->SetWidth(object->GetWidth());
				gameObject->SetHeight(object->GetHeight());

				_quadTree->Insert(gameObject);
			}
		}
	}
}

GameMap::~GameMap()
{
	delete _map;

	for (size_t i = 0; i < _listApples.size(); i++)
	{
		if (_listApples[i])
			delete _listApples[i];
	}
	_listApples.clear();

	/*don't use tileset for this game
	for (size_t i = 0; i < _listTileSet.size(); i++)
	{
		if (_listTileSet[i])
			delete _listTileSet[i];
	}
	_listTileSet.clear();
	*/

	_quadTree->Clear();
	delete _quadTree;
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
		//remove not visible apple
		if (!_listApples[i]->IsVisible())
		{
			delete _listApples[i];
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
		//remove not visible apple
		if (!_listFloatGrounds[i]->IsVisible())
		{
			delete _listFloatGrounds[i];
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
}

int GameMap::GetWidth()
{
	return _map->GetWidth() * _map->GetTileWidth();
}

int GameMap::GetHeight()
{
	return _map->GetHeight() * _map->GetTileHeight();
}