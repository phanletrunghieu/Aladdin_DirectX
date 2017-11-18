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

void MainScene::Update(float dt)
{
	Scene::Update(dt);

	_txtCountApple->SetString(_gameMap->GetPlayer()->GetNumAppleWeapon());
	_playerHealthMeter->ChangeAnimation(_gameMap->GetPlayer()->GetHealth());
	_playerHealthMeter->Update(dt);
}

void MainScene::Draw()
{
	_backgroundTextures[0]->Draw(_camera);
	Scene::Draw();
	_backgroundTextures[1]->Draw(_camera);

	_spriteCountApple->Draw(D3DXVECTOR3(Graphics::GetInstance()->GetScreenWidth() - 80, Graphics::GetInstance()->GetScreenHeight() - 50, 0));
	_txtCountApple->Draw(D3DXVECTOR2(Graphics::GetInstance()->GetScreenWidth() - 50, Graphics::GetInstance()->GetScreenHeight() - 50));
	_playerHealthMeter->Draw(D3DXVECTOR3(_playerHealthMeter->GetWidth() / 2 + 10, _playerHealthMeter->GetHeight() / 2 + 10, 0));
}
