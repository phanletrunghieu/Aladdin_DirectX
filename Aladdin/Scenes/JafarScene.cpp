#include "JafarScene.h"
#include "../GameComponents/Sound.h"

JafarScene::JafarScene() :Scene(0x9090b0)
{
	LoadContent();
}

JafarScene::~JafarScene()
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

void JafarScene::LoadContent()
{
	Sprite* sprite;
	RECT sourceRect;

	sourceRect.left = 0;
	sourceRect.right = 1259;
	sourceRect.top = 0;
	sourceRect.bottom = 563;

	sprite = new Sprite(ResourceManager::GetInstance()->GetTextureMapBoss(), true, sourceRect);
	sprite->SetPosition(sprite->GetWidth() / 2.0f, sprite->GetHeight() / 2.0f);
	_backgroundTextures.push_back(sprite);

	_gameMap = new GameMap("Resources/Maps/JafarPlace/MapBoss.tmx", _quadTree);
	_camera = new Camera(_gameMap->GetPlayer());

	RECT appleSourceRect;
	appleSourceRect.left = 341;
	appleSourceRect.right = 352;
	appleSourceRect.top = 17;
	appleSourceRect.bottom = 29;
	_spriteCountApple = new Sprite(ResourceManager::GetInstance()->GetTextureItems(), true, appleSourceRect);
	_spriteCountApple->SetScale(D3DXVECTOR2(2, 2));
	_txtCountApple = new Text(L"0", 15, 15, FW_BOLD);

	_playHealthMeter = new PlayerHealthMeter();

	Sound::GetInstance()->Play("Jafar_Laugh", 0, 1);
}

void JafarScene::Update(float deltatime)
{
	Scene::Update(deltatime);

	_txtCountApple->SetString(_gameMap->GetPlayer()->GetNumAppleWeapon());
	_playHealthMeter->ChangeAnimation(_gameMap->GetPlayer()->GetHealth());
	_playHealthMeter->Update(deltatime);
}

void JafarScene::Draw()
{
	_backgroundTextures[0]->Draw(_camera);
	Scene::Draw();

	_spriteCountApple->Draw(D3DXVECTOR3(Graphics::GetInstance()->GetScreenWidth() - 80, Graphics::GetInstance()->GetScreenHeight() - 50, 0));
	_txtCountApple->Draw(D3DXVECTOR2(Graphics::GetInstance()->GetScreenWidth() - 50, Graphics::GetInstance()->GetScreenHeight() - 50));
	_playHealthMeter->Draw(D3DXVECTOR3(_playHealthMeter->GetWidth() / 2 + 10, _playHealthMeter->GetHeight() / 2 + 10, 0));
}