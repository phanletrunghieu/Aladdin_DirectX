#include "PlayerHealthMeter.h"



PlayerHealthMeter::PlayerHealthMeter()
{
	_animation10 = new Animation(ResourceManager::GetInstance()->GetAnimationXMLPlayerHealthMeter(), "100", ResourceManager::GetInstance()->GetTextureItems(), true, 0.5f);
	_animation10->SetScale(D3DXVECTOR2(1.5f, 1.5f));

	_animation9 = new Animation(ResourceManager::GetInstance()->GetAnimationXMLPlayerHealthMeter(), "90", ResourceManager::GetInstance()->GetTextureItems(), true, 0.5f);
	_animation9->SetScale(D3DXVECTOR2(1.5f, 1.5f));

	_animation8 = new Animation(ResourceManager::GetInstance()->GetAnimationXMLPlayerHealthMeter(), "80", ResourceManager::GetInstance()->GetTextureItems(), true, 0.5f);
	_animation8->SetScale(D3DXVECTOR2(1.5f, 1.5f));

	_animation7 = new Animation(ResourceManager::GetInstance()->GetAnimationXMLPlayerHealthMeter(), "70", ResourceManager::GetInstance()->GetTextureItems(), true, 0.5f);
	_animation7->SetScale(D3DXVECTOR2(1.5f, 1.5f));

	_animation6 = new Animation(ResourceManager::GetInstance()->GetAnimationXMLPlayerHealthMeter(), "60", ResourceManager::GetInstance()->GetTextureItems(), true, 0.5f);
	_animation6->SetScale(D3DXVECTOR2(1.5f, 1.5f));

	_animation5 = new Animation(ResourceManager::GetInstance()->GetAnimationXMLPlayerHealthMeter(), "50", ResourceManager::GetInstance()->GetTextureItems(), true, 0.5f);
	_animation5->SetScale(D3DXVECTOR2(1.5f, 1.5f));

	_animation4 = new Animation(ResourceManager::GetInstance()->GetAnimationXMLPlayerHealthMeter(), "40", ResourceManager::GetInstance()->GetTextureItems(), true, 0.5f);
	_animation4->SetScale(D3DXVECTOR2(1.5f, 1.5f));

	_animation3 = new Animation(ResourceManager::GetInstance()->GetAnimationXMLPlayerHealthMeter(), "30", ResourceManager::GetInstance()->GetTextureItems(), true, 0.5f);
	_animation3->SetScale(D3DXVECTOR2(1.5f, 1.5f));

	_animation2 = new Animation(ResourceManager::GetInstance()->GetAnimationXMLPlayerHealthMeter(), "20", ResourceManager::GetInstance()->GetTextureItems(), true, 0.5f);
	_animation2->SetScale(D3DXVECTOR2(1.5f, 1.5f));

	_animation1 = new Animation(ResourceManager::GetInstance()->GetAnimationXMLPlayerHealthMeter(), "10", ResourceManager::GetInstance()->GetTextureItems(), true, 0.5f);
	_animation1->SetScale(D3DXVECTOR2(1.5f, 1.5f));

	_animation0 = new Animation(ResourceManager::GetInstance()->GetAnimationXMLPlayerHealthMeter(), "0", ResourceManager::GetInstance()->GetTextureItems(), true, 0.5f);
	_animation0->SetScale(D3DXVECTOR2(1.5f, 1.5f));

	_currentAnimation = _animation10;

	_width = _currentAnimation->GetWidth() * _currentAnimation->GetScale().x;
	_height = _currentAnimation->GetHeight() * _currentAnimation->GetScale().y;
}


PlayerHealthMeter::~PlayerHealthMeter()
{
	delete _animation10;
	delete _animation9;
	delete _animation8;
	delete _animation7;
	delete _animation6;
	delete _animation5;
	delete _animation4;
	delete _animation3;
	delete _animation2;
	delete _animation1;
	delete _animation0;
}

void PlayerHealthMeter::Draw(D3DXVECTOR3 position)
{
	_currentAnimation->Draw(position);
}

void PlayerHealthMeter::Update(float deltaTime)
{
	GameObject::Update(deltaTime);

	_currentAnimation->Update(deltaTime);

	_width = _currentAnimation->GetWidth() * _currentAnimation->GetScale().x;
	_height = _currentAnimation->GetHeight() * _currentAnimation->GetScale().y;
}

void PlayerHealthMeter::ChangeAnimation(int value)
{
	if (value == 100)
		_currentAnimation = _animation10;
	else if(value >= 90)
		_currentAnimation = _animation9;
	else if(value >= 80)
		_currentAnimation = _animation8;
	else if (value >= 70)
		_currentAnimation = _animation7;
	else if (value >= 60)
		_currentAnimation = _animation6;
	else if (value >= 50)
		_currentAnimation = _animation5;
	else if (value >= 40)
		_currentAnimation = _animation4;
	else if (value >= 30)
		_currentAnimation = _animation3;
	else if (value >= 20)
		_currentAnimation = _animation2;
	else if (value >= 10)
		_currentAnimation = _animation1;
	else if (value >= 0)
		_currentAnimation = _animation0;
}
