#include "Bottle.h"



Bottle::Bottle() : GameObject(GameObject::GameObjectType::Bottles, false)
{
	_animation = new Animation(ResourceManager::GetInstance()->GetAnimationXMLBottle(), "bottle", ResourceManager::GetInstance()->GetTextureItems(), true, 0.5f, false);
	_animation->Pause();
	_width = _animation->GetWidth();
	_height = _animation->GetHeight();
}


Bottle::~Bottle()
{
	if (_animation)
	{
		delete _animation;
		_animation = NULL;
	}
}

void Bottle::Draw(Camera * camera)
{
	_animation->Draw(camera);
}

void Bottle::Update(float deltaTime)
{
	GameObject::Update(deltaTime);

	_animation->SetPosition(_position);
	_animation->Update(deltaTime);
	SetPosition(_animation->GetPosition());

	_width = _animation->GetWidth();
	_height = _animation->GetHeight();
}

void Bottle::OnCollision(GameObject * target, GameCollision::SideCollisions side)
{
	if (target->GetTag() == GameObject::GameObjectType::Players && _animation->IsPaused() && !_animation->IsFinish())
	{
		_animation->Play();
	}
}
