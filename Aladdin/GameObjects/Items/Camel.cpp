#include "Camel.h"
#include "../Player/Player.h"
#include "../Weapons/PlayerWeapons/CamelWeapon.h"
#include "../../GameComponents/SceneManager.h"

Camel::Camel() : GameObject(GameObject::GameObjectType::Camels, false)
{
	_animation = new Animation(ResourceManager::GetInstance()->GetAnimationXMLCamel(), "Camel", ResourceManager::GetInstance()->GetTextureCamel(), true, 0.3f, false);
	_width = _animation->GetWidth();
	_height = _animation->GetHeight();

	_isCreatedWeapon = false;
}


Camel::~Camel()
{
	if (_animation)
	{
		delete _animation;
		_animation = NULL;
	}
}

void Camel::Draw(Camera * camera)
{
	_animation->Draw(camera);
}

void Camel::Update(float deltaTime)
{
	GameObject::Update(deltaTime);

	_animation->SetPosition(_position);
	_animation->Update(deltaTime);
	SetPosition(_animation->GetPosition());

	_width = _animation->GetWidth();
	_height = _animation->GetHeight();

	if (!_isCreatedWeapon && _animation->GetCurrentIndex() == 5)
	{
		_isCreatedWeapon = true;
		CamelWeapon* weapon = new CamelWeapon();

		weapon->SetPosition(_position);

		//add gameobject to update&draw list
		SceneManager::GetInstance()->GetCurrentScene()->AddGameObjectToWeaponList(weapon);

		//add appleWeapon to QuadTree
		QuadTree::InsertDynamicObject(weapon);
	}

	//reset _isCreatedWeapon

	if (_animation->IsFinish())
	{
		_isCreatedWeapon = false;
		_animation->Pause();
	}
}

void Camel::OnCollision(GameObject * target, GameCollision::SideCollisions side)
{
	if (target->GetTag() == GameObject::GameObjectType::Players
		&& (side == GameCollision::SideCollisions::Top
			|| side == GameCollision::SideCollisions::TopLeft
			|| side == GameCollision::SideCollisions::TopRight))
	{
		Player* player = dynamic_cast<Player*>(target);
		if (player->GetState()->GetName() == PlayerState::StateName::Fall || player->GetState()->GetName() == PlayerState::StateName::RunFall)
		{
			_animation->SetCurrentIndex(0);
			_animation->Play();
		}
	}
}
