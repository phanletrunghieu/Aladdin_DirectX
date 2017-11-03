#include "Enemy1AttackState.h"
#include "Enemy1.h"


Enemy1AttackState::Enemy1AttackState()
{
	//not use
}

Enemy1AttackState::Enemy1AttackState(Enemy * enemy) : EnemyState(enemy, EnemyState::StateName::Attack)
{
	SetAnimation(new Animation(ResourceManager::GetInstance()->GetAnimationXMLEnemy1(), "Attack", ResourceManager::GetInstance()->GetTextureEnemies1(), false, 0.8f));
}


Enemy1AttackState::~Enemy1AttackState()
{
}

void Enemy1AttackState::Update(float deltaTime)
{
	EnemyState::Update(deltaTime);

	//change state
	if (!_enemy->IsTargetInAttackRange() && _enemy->GetTarget()->GetVelocity().x != 0)
	{
		_enemy->SetState(new Enemy1WalkState(_enemy));
		return;
	}
}
