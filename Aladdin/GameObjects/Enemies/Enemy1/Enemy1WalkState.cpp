#include "Enemy1WalkState.h"
#include "Enemy1.h"
#include "Enemy1AttackState.h"
#include "Enemy1IdleState.h"

Enemy1WalkState::Enemy1WalkState()
{
}

Enemy1WalkState::Enemy1WalkState(Enemy * enemy) : EnemyState(enemy, EnemyState::StateName::Walk)
{
	SetAnimation(new Animation(ResourceManager::GetInstance()->GetAnimationXMLEnemy1(), "Walk", ResourceManager::GetInstance()->GetTextureEnemies1(), false, 0.7f));
}


Enemy1WalkState::~Enemy1WalkState()
{
}

void Enemy1WalkState::Update(float deltaTime)
{
	EnemyState::Update(deltaTime);

	//change state
	if (_enemy->GetVelocity().x == 0)//change state
	{
		_enemy->SetState(new Enemy1IdleState(_enemy));
		return;
	}

	if (_enemy->IsTargetInAttackRange())
	{
		_enemy->SetState(new Enemy1AttackState(_enemy));
		return;
	}
}
