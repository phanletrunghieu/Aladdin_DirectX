#include "Enemy5AttackState.h"
#include "Enemy5.h"
#include "Enemy5WalkState.h"

Enemy5AttackState::Enemy5AttackState()
{
	//not use
}

Enemy5AttackState::Enemy5AttackState(Enemy * enemy) : EnemyState(enemy, EnemyState::StateName::Attack)
{
	SetAnimation(new Animation(ResourceManager::GetInstance()->GetAnimationXMLEnemy5(), "Attack", ResourceManager::GetInstance()->GetTextureEnemies2(), true, 1.0f));
}


Enemy5AttackState::~Enemy5AttackState()
{
}

void Enemy5AttackState::Update(float deltaTime)
{
	EnemyState::Update(deltaTime);

	//change state
	if (!_enemy->IsTargetInAttackRange() && _enemy->GetTarget()->GetVelocity().x != 0)
	{
		_enemy->SetState(new Enemy5WalkState(_enemy));
		return;
	}
}
