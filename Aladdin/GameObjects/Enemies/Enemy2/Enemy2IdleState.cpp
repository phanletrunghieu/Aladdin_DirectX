#include "Enemy2IdleState.h"
#include "Enemy2.h"
#include "Enemy2WalkState.h"
#include "Enemy2AttackState.h"

Enemy2IdleState::Enemy2IdleState()
{
	//not use
}

Enemy2IdleState::Enemy2IdleState(Enemy * enemy) : EnemyState(enemy, EnemyState::StateName::Idle)
{
	SetAnimation(new Animation(ResourceManager::GetInstance()->GetAnimationXMLEnemy2(), "Idle", ResourceManager::GetInstance()->GetTextureEnemies1(), false, 0.8f));
}


Enemy2IdleState::~Enemy2IdleState()
{
}

void Enemy2IdleState::Update(float deltaTime)
{
	EnemyState::Update(deltaTime);

	//change state
	if (_enemy->GetVelocity().x != 0)
	{
		_enemy->SetState(new Enemy2WalkState(_enemy));
		return;
	}

	if (_enemy->IsTargetInAttackRange())
	{
		_enemy->SetState(new Enemy2AttackState(_enemy));
		return;
	}
}
