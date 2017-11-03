#include "Enemy5IdleState.h"
#include "Enemy5.h"


Enemy5IdleState::Enemy5IdleState()
{
	//not use
}

Enemy5IdleState::Enemy5IdleState(Enemy * enemy) : EnemyState(enemy, EnemyState::StateName::Idle)
{
	SetAnimation(new Animation(ResourceManager::GetInstance()->GetAnimationXMLEnemy5(), "Idle", ResourceManager::GetInstance()->GetTextureEnemies2(), true, 0.8f));
}


Enemy5IdleState::~Enemy5IdleState()
{
}

void Enemy5IdleState::Update(float deltaTime)
{
	EnemyState::Update(deltaTime);

	//change state
	if (_totalDuration >= 10)
	{
		_totalDuration = 0;
		_enemy->SetState(new Enemy5LookState(_enemy));
		return;
	}

	if (_enemy->GetVelocity().x != 0)
	{
		_enemy->SetState(new Enemy5WalkState(_enemy));
		return;
	}

	if (_enemy->IsTargetInAttackRange())
	{
		_enemy->SetState(new Enemy5AttackState(_enemy));
		return;
	}
}
