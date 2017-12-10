#include "Coal.h"

Coal::Coal() : GameObject(GameObject::GameObjectType::Coal, true)
{
	_animationCoalToFire = new Animation(ResourceManager::GetInstance()->GetAnimationXMLCoalFire(), "fire", ResourceManager::GetInstance()->GetTextureBossJafar(), true, 0.9f, false);
	_animationCoalToFire->Pause();
	_isDrawFire = false;
}


Coal::~Coal()
{
}

void Coal::Update(float deltaTime)
{
	GameObject::Update(deltaTime);

	if (_isUpdateFire)
	{
		_isUpdateFire = false;
		_animationCoalToFire->SetCurrentIndex(0);
		_animationCoalToFire->Play();
	}

	if (_animationCoalToFire->IsFinish())
	{
		_isDrawFire = false;
		_animationCoalToFire->Pause();
	}

	_animationCoalToFire->Update(_deltaTime);
}

void Coal::Draw(Camera * camera)
{
	if (_isDrawFire)
	{
		_animationCoalToFire->Draw(camera);
	}
}

void Coal::OnCollision(GameObject * target, GameCollision::SideCollisions side)
{
	if (target->GetTag() == GameObject::GameObjectType::Players && _isDrawFire == false)
	{
		_isDrawFire = true;
		_isUpdateFire = true;
		_animationCoalToFire->SetPosition(target->GetPosition().x, target->GetPosition().y);
	}
}