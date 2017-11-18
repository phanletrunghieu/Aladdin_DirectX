#include "Enemy5WalkState.h"
#include "Enemy5.h"
#include "Enemy5IdleState.h"
#include "Enemy5AttackState.h"

Enemy5WalkState::Enemy5WalkState()
{
	//not use
}

Enemy5WalkState::Enemy5WalkState(Enemy * enemy) : EnemyState(enemy, EnemyState::StateName::Walk)
{
	SetAnimation(new Animation(ResourceManager::GetInstance()->GetAnimationXMLEnemy5(), "Walk", ResourceManager::GetInstance()->GetTextureEnemies2(), true, 0.8f));
}

Enemy5WalkState::~Enemy5WalkState()
{
}

void Enemy5WalkState::Update(float deltaTime)
{
	EnemyState::Update(deltaTime);

	//change state
	if (_enemy->GetVelocity().x == 0)//change state
	{
		_enemy->SetState(new Enemy5IdleState(_enemy));
		return;
	}

	if (_enemy->IsTargetInAttackRange())
	{
		_enemy->SetState(new Enemy5AttackState(_enemy));
		return;
	}
}
