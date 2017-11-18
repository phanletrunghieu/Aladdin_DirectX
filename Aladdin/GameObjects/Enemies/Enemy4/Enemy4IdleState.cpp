#include "Enemy4IdleState.h"
#include "Enemy4.h"
#include "../../Weapons/EnemiesWeapons/Enemy3Weapon.h"
#include "../../../GameComponents/SceneManager.h"


Enemy4IdleState::Enemy4IdleState()
{
	//not use
}

Enemy4IdleState::Enemy4IdleState(Enemy * enemy) : EnemyState(enemy, EnemyState::StateName::Idle)
{
	SetAnimation(new Animation(ResourceManager::GetInstance()->GetAnimationXMLEnemy4(), "Idle", ResourceManager::GetInstance()->GetTextureEnemies2(), true, 0.5f));
}


Enemy4IdleState::~Enemy4IdleState()
{
}

void Enemy4IdleState::Update(float deltaTime)
{
	EnemyState::Update(deltaTime);

	//create weapon
	if (_totalDuration >= 3 && _enemy->IsTargetInAttackRange())
	{
		_totalDuration = 0;

		Enemy3Weapon* weapon = new Enemy3Weapon();
		weapon->SetPosition(_enemy->GetPosition().x, _enemy->GetPosition().y - _enemy->GetHeight() / 2);

		//set left or right for velocityX
		weapon->SetVelocity(_enemy->GetTarget()->GetPosition() - _enemy->GetPosition());

		//add gameobject to update&draw list
		SceneManager::GetInstance()->GetCurrentScene()->AddGameObjectToWeaponList(weapon);

		//add appleWeapon to QuadTree
		QuadTree::InsertDynamicObject(weapon);
	}
}
