#include "Enemy2WalkState.h"
#include "Enemy2.h"


Enemy2WalkState::Enemy2WalkState()
{
}

Enemy2WalkState::Enemy2WalkState(Enemy * enemy) : EnemyState(enemy, EnemyState::StateName::Walk)
{
	SetAnimation(new Animation(ResourceManager::GetInstance()->GetAnimationXMLEnemy2(), "Walk", ResourceManager::GetInstance()->GetTextureEnemies(), 0.7f));
}


Enemy2WalkState::~Enemy2WalkState()
{
}

void Enemy2WalkState::Update(float deltaTime)
{
	EnemyState::Update(deltaTime);

	//change state
	if (_enemy->GetVelocity().x == 0)//change state
	{
		_enemy->SetState(new Enemy2IdleState(_enemy));
		return;
	}

	if (_enemy->IsTargetInAttackRange())
	{
		_enemy->SetState(new Enemy2AttackState(_enemy));
		return;
	}
}
