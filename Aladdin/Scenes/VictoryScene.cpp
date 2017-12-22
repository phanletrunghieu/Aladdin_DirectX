#include "VictoryScene.h"
#include "../GameComponents/Graphics.h"

VictoryScene::VictoryScene() :Scene(Scene::SceneName::VictoryScenes, 0x000000)
{
	LoadContent();
}

VictoryScene::~VictoryScene()
{
	delete _title;
	_title = NULL;

	delete _animationAladdin;
	_animationAladdin = NULL;

	delete _animationMonkey;
	_animationMonkey = NULL;
}

void VictoryScene::LoadContent()
{
	_camera = new Camera(NULL);

	_title = new Text(L"Mission Complete", 40, 50, FW_BOLD);
	_animationAladdin=new Animation(ResourceManager::GetInstance()->GetAnimationXMLAladdin(), "Win", ResourceManager::GetInstance()->GetTextureAladdin(), true, 1.5f);
	_animationMonkey = new Animation(ResourceManager::GetInstance()->GetAnimationXMLMonkey(), "Win", ResourceManager::GetInstance()->GetTextureMonkey(), true, 1.5f);
	
	_animationAladdin->SetPosition(Graphics::GetInstance()->GetScreenWidth(), Graphics::GetInstance()->GetScreenHeight() / 2);
	_animationMonkey->SetPosition(Graphics::GetInstance()->GetScreenWidth()-100, Graphics::GetInstance()->GetScreenHeight() / 2);
}

void VictoryScene::Update(float deltatime)
{
	//Scene::Update(deltatime);

	D3DXVECTOR2 _positonAladin= _animationAladdin->GetPosition();
	D3DXVECTOR2 _positonMonkey = _animationMonkey->GetPosition();

	_animationAladdin->SetPosition(_positonAladin.x - 2*deltatime, _positonAladin.y);
	_animationMonkey->SetPosition(_positonMonkey.x - 2*deltatime, _positonMonkey.y);

	_animationAladdin->Update(deltatime);
	_animationMonkey->Update(deltatime);
}

void VictoryScene::Draw()
{
	//Scene::Draw();
	_title->Draw(D3DXVECTOR2(Graphics::GetInstance()->GetScreenWidth()/2 - 300, 50));
	_animationAladdin->Draw(_camera);
	_animationMonkey->Draw(_camera);
}
