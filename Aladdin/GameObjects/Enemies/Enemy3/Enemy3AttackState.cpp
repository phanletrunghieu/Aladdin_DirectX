#include "Enemy3AttackState.h"
#include "Enemy3.h"
#include "Enemy3WalkState.h"
#include "../../Weapons/EnemiesWeapons/Enemy3Weapon.h"
#include "../../../GameComponents/SceneManager.h"

Enemy3AttackState::Enemy3AttackState()
{
	//not use
}

Enemy3AttackState::Enemy3AttackState(Enemy * enemy) : EnemyState(enemy, EnemyState::StateName::Attack)
{
	SetAnimation(new Animation(ResourceManager::GetInstance()->GetAnimationXMLEnemy3(), "Attack", ResourceManager::GetInstance()->GetTextureEnemies1(), false, 1.0f));

	_isCreatedWeapon = false;
}


Enemy3AttackState::~Enemy3AttackState()
{
}

void Enemy3AttackState::Update(float deltaTime)
{
	EnemyState::Update(deltaTime);

	//create weapon
	if (!_isCreatedWeapon && _animation->GetCurrentIndex() == 2)
	{
		_isCreatedWeapon = true;

		Enemy3Weapon* weapon = new Enemy3Weapon();
		weapon->SetPosition(_enemy->GetPosition().x, _enemy->GetPosition().y - _enemy->GetHeight() / 2);

		//set left or right for velocityX
		weapon->SetVelocity(_enemy->GetTarget()->GetPosition() - _enemy->GetPosition());
		
		//add gameobject to update&draw list
		SceneManager::GetInstance()->GetCurrentScene()->AddGameObjectToWeaponList(weapon);

		//add appleWeapon to QuadTree
		QuadTree::InsertDynamicObject(weapon);
	}
	//reset _isCreatedWeapon
	if (_animation->GetCurrentIndex() == 3)
		_isCreatedWeapon = false;

	//change state
	if (!_enemy->IsTargetInAttackRange() && _enemy->GetTarget()->GetVelocity().x != 0)
	{
		_enemy->SetState(new Enemy3WalkState(_enemy));
		return;
	}
}
