#include "Enemy1IdleState.h"
#include "Enemy1.h"
#include "Enemy1WalkState.h"
#include "Enemy1AttackState.h"

Enemy1IdleState::Enemy1IdleState()
{
	//not use
}

Enemy1IdleState::Enemy1IdleState(Enemy * enemy) : EnemyState(enemy, EnemyState::StateName::Idle)
{
	SetAnimation(new Animation(ResourceManager::GetInstance()->GetAnimationXMLEnemy1(), "Idle", ResourceManager::GetInstance()->GetTextureEnemies1(), false));
}


Enemy1IdleState::~Enemy1IdleState()
{
}

void Enemy1IdleState::Update(float deltaTime)
{
	EnemyState::Update(deltaTime);

	//change state
	if (_enemy->GetVelocity().x != 0)
	{
		_enemy->SetState(new Enemy1WalkState(_enemy));
		return;
	}

	if (_enemy->IsTargetInAttackRange())
	{
		_enemy->SetState(new Enemy1AttackState(_enemy));
		return;
	}
}
