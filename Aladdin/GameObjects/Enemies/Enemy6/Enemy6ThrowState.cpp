#include "Enemy6ThrowState.h"
#include "Enemy6.h"
#include "../../Weapons/EnemiesWeapons/Enemy6Weapon.h"
#include "../../../GameComponents/SceneManager.h"

Enemy6ThrowState::Enemy6ThrowState()
{
	//not use
}

Enemy6ThrowState::Enemy6ThrowState(Enemy * enemy) : EnemyState(enemy, EnemyState::StateName::Idle)
{
	SetAnimation(new Animation(ResourceManager::GetInstance()->GetAnimationXMLEnemy6(), "throw", ResourceManager::GetInstance()->GetTextureEnemies2(), true, 0.8f));
	_isCreatedWeapon = false;
}


Enemy6ThrowState::~Enemy6ThrowState()
{
}

void Enemy6ThrowState::Update(float deltaTime)
{
	EnemyState::Update(deltaTime);

	//temp pause
	if (_animation->IsFinish())
	{
		_animation->Pause();
		_animation->SetCurrentIndex(0);
		_totalDuration = 0;
	}

	//resume after 2s
	if (_totalDuration >= 3) {
		_animation->Play();
		_totalDuration = 0;
	}

	//create weapon
	if (!_isCreatedWeapon && _animation->GetCurrentIndex() == 6)
	{
		_isCreatedWeapon = true;

		Enemy6Weapon* weapon = new Enemy6Weapon();
		weapon->SetPosition(_enemy->GetPosition());

		//add gameobject to update&draw list
		SceneManager::GetInstance()->GetCurrentScene()->AddGameObjectToWeaponList(weapon);

		//add appleWeapon to QuadTree
		QuadTree::InsertDynamicObject(weapon);
	}
	//reset _isCreatedWeapon
	if (_animation->GetCurrentIndex() == 7)
		_isCreatedWeapon = false;
}
