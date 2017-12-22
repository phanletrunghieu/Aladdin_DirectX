#include "DefeatScene.h"
#include "../GameComponents/Graphics.h"

DefeatScene::DefeatScene() :Scene(Scene::SceneName::DefeatScenes, 0x000000)
{
	LoadContent();
}

DefeatScene::~DefeatScene()
{
	delete _title;
	_title = NULL;

	delete _animationAladdin;
	_animationAladdin = NULL;
}

void DefeatScene::LoadContent()
{
	_camera = new Camera(NULL);

	_title = new Text(L"DEFEAT", 40, 50, FW_BOLD);
	_animationAladdin = new Animation(ResourceManager::GetInstance()->GetAnimationXMLAladdin(), "Lose", ResourceManager::GetInstance()->GetTextureAladdin(), true, 1.5f);
	
	_animationAladdin->SetPosition(Graphics::GetInstance()->GetScreenWidth()/2, Graphics::GetInstance()->GetScreenHeight() / 2);
}

void DefeatScene::Update(float deltatime)
{
	_animationAladdin->Update(deltatime);

	if (_animationAladdin->IsFinish())
	{
		_animationAladdin->Pause();
	}
}

void DefeatScene::Draw()
{
	_title->Draw(D3DXVECTOR2(Graphics::GetInstance()->GetScreenWidth() / 2 - 150, 50));
	_animationAladdin->Draw(_camera);
}