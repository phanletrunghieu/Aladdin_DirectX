#include "Enemy5LookState.h"
#include "Enemy5.h"
#include "Enemy5IdleState.h"
#include "Enemy5WalkState.h"
#include "Enemy5AttackState.h"

Enemy5LookState::Enemy5LookState()
{
	//not use
}

Enemy5LookState::Enemy5LookState(Enemy * enemy) : EnemyState(enemy, EnemyState::StateName::Idle)
{
	SetAnimation(new Animation(ResourceManager::GetInstance()->GetAnimationXMLEnemy5(), "Look", ResourceManager::GetInstance()->GetTextureEnemies2(), true, 0.8f,  false));
}


Enemy5LookState::~Enemy5LookState()
{
}

void Enemy5LookState::Update(float deltaTime)
{
	EnemyState::Update(deltaTime);

	//change state
	if (_animation->IsFinish())
	{
		_enemy->SetState(new Enemy5IdleState(_enemy));
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
