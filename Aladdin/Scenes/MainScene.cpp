#include "MainScene.h"

MainScene::MainScene():Scene(0x9090b0)
{
	LoadContent();
}

MainScene::~MainScene()
{
	for (size_t i = 0; i < _backgroundTextures.size(); i++)
	{
		delete _backgroundTextures[i];
		_backgroundTextures[i] = NULL;
	}
	_backgroundTextures.clear();

	delete _gameMap;
	_gameMap = NULL;

	delete _txtCountApple;
	_txtCountApple = NULL;
}

void MainScene::LoadContent()
{
	Sprite *sprite;
	RECT sourceRect;

	sourceRect.left = 0;
	sourceRect.right = 4773;
	sourceRect.top = 0;
	sourceRect.bottom = 689;

	sprite = new Sprite(ResourceManager::GetInstance()->GetTextureAgrabahMarket(), true, sourceRect);
	sprite->SetPosition(sprite->GetWidth() / 2.0f, sprite->GetHeight() / 2.0f);
	_backgroundTextures.push_back(sprite);

	sourceRect.top = 689;
	sourceRect.bottom = 1378;
	sprite = new Sprite(ResourceManager::GetInstance()->GetTextureAgrabahMarket(), true, sourceRect);
	sprite->SetPosition(sprite->GetWidth() / 2.0f, sprite->GetHeight() / 2.0f);
	_backgroundTextures.push_back(sprite);

	_gameMap = new GameMap("Resources/Maps/AgrabahMarket/AgrabahMarket.tmx", _quadTree);

	_camera = new Camera(_gameMap->GetPlayer());

	//apple weapon
	RECT appleSourceRect;
	appleSourceRect.left = 341;
	appleSourceRect.right = 352;
	appleSourceRect.top = 17;
	appleSourceRect.bottom = 29;
	_spriteCountApple = new Sprite(ResourceManager::GetInstance()->GetTextureItems(), true, appleSourceRect);
	_spriteCountApple->SetScale(D3DXVECTOR2(2, 2));
	_txtCountApple = new Text(L"0", 15, 15, FW_BOLD);

	_playerHealthMeter = new PlayerHealthMeter();
}

void MainScene::CheckCollision()
{
#pragma region check collision with player
	std::vector<GameObject*> listCanCollisionWithPlayer;

	//get all object that can collision
	_quadTree->Retrieve(listCanCollisionWithPlayer, _gameMap->GetPlayer());

	bool playerGround = false;
	bool allowPlayerMoveLeft = true;
	bool allowPlayerMoveRight = true;

	for (size_t i = 0; i < listCanCollisionWithPlayer.size(); i++)
	{
		GameObject *gameObject = listCanCollisionWithPlayer.at(i);
		if (!gameObject->IsVisible())
			continue;

		//lay va cham cua player voi gameobject
		GameCollision collisionDataOfOtherObj = GameCollision::CheckCollision(gameObject->GetBound(), _gameMap->GetPlayer()->GetBound());
		if (collisionDataOfOtherObj.IsCollided())
			gameObject->OnCollision(_gameMap->GetPlayer(), collisionDataOfOtherObj.GetSide());

		//lay va cham cua gameobject voi player
		GameCollision collisionDataOfPlayer = GameCollision::CheckCollision(_gameMap->GetPlayer()->GetBound(), gameObject->GetBound());
		if (collisionDataOfPlayer.IsCollided())
		{
			_gameMap->GetPlayer()->OnCollision(gameObject, collisionDataOfPlayer.GetSide());


			if (gameObject->GetTag() == GameObject::GameObjectType::Ground || gameObject->GetTag() == GameObject::GameObjectType::FloatGround)
			{
				if (collisionDataOfPlayer.GetSide()==GameCollision::SideCollisions::Bottom)
					playerGround = true;

				if (collisionDataOfPlayer.GetSide() == GameCollision::SideCollisions::Left)
					allowPlayerMoveLeft = false;
				if (collisionDataOfPlayer.GetSide() == GameCollision::SideCollisions::Right)
					allowPlayerMoveRight = false;
			}
		}
	}
	_gameMap->GetPlayer()->SetIsGround(playerGround);

	//because climb state has own move rule
	if (_gameMap->GetPlayer()->GetState()->GetName() != PlayerState::StateName::ClimbVertical && _gameMap->GetPlayer()->GetState()->GetName() != PlayerState::StateName::ClimbAttack)
	{
		_gameMap->GetPlayer()->AllowMoveLeft(allowPlayerMoveLeft);
		_gameMap->GetPlayer()->AllowMoveRight(allowPlayerMoveRight);
	}
#pragma endregion

#pragma region Check collision with weapon
	for (size_t i = 0; i < _listWeapon.size(); i++)
	{
		std::vector<GameObject*> listCanCollisionWithAppleWeapon;

		//get all object that can collision
		_quadTree->Retrieve(listCanCollisionWithAppleWeapon, _listWeapon[i]);

		for (size_t j = 0; j < listCanCollisionWithAppleWeapon.size(); j++)
		{
			GameObject *gameObject = listCanCollisionWithAppleWeapon.at(j);
			if (!gameObject->IsVisible())
				continue;

			//lay va cham cua weapon voi gameobject
			GameCollision collisionDataOfOtherObj = GameCollision::CheckCollision(gameObject->GetBound(), _listWeapon[i]->GetBound());
			if (collisionDataOfOtherObj.IsCollided())
				gameObject->OnCollision(_listWeapon[i], collisionDataOfOtherObj.GetSide());

			//lay va cham cua gameobject voi weapon
			GameCollision collisionDataOfWeapon = GameCollision::CheckCollision(_listWeapon[i]->GetBound(), gameObject->GetBound());
			if (collisionDataOfWeapon.IsCollided())
				_listWeapon[i]->OnCollision(gameObject, collisionDataOfWeapon.GetSide());
		}
	}
#pragma endregion

}

void MainScene::Update(float dt)
{
	Scene::Update(dt);

	CheckCollision();

	_gameMap->Update(dt);
	_camera->Update(dt);

	_txtCountApple->SetString(_gameMap->GetPlayer()->GetNumAppleWeapon());
	_playerHealthMeter->ChangeAnimation(_gameMap->GetPlayer()->GetHealth());
	_playerHealthMeter->Update(dt);
}

void MainScene::Draw()
{
	_backgroundTextures[0]->Draw(_camera);
	_gameMap->Draw(_camera);
	_backgroundTextures[1]->Draw(_camera);

	_spriteCountApple->Draw(D3DXVECTOR3(Graphics::GetInstance()->GetScreenWidth() - 80, Graphics::GetInstance()->GetScreenHeight() - 50, 0));
	_txtCountApple->Draw(D3DXVECTOR2(Graphics::GetInstance()->GetScreenWidth() - 50, Graphics::GetInstance()->GetScreenHeight() - 50));
	_playerHealthMeter->Draw(D3DXVECTOR3(_playerHealthMeter->GetWidth() / 2 + 10, _playerHealthMeter->GetHeight() / 2 + 10, 0));
	
	Scene::Draw();
}
