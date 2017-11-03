#include "Enemy3IdleState.h"
#include "Enemy3.h"


Enemy3IdleState::Enemy3IdleState()
{
	//not use
}

Enemy3IdleState::Enemy3IdleState(Enemy * enemy) : EnemyState(enemy, EnemyState::StateName::Idle)
{
	SetAnimation(new Animation(ResourceManager::GetInstance()->GetAnimationXMLEnemy3(), "Idle", ResourceManager::GetInstance()->GetTextureEnemies1(), false, 0.8f));
}


Enemy3IdleState::~Enemy3IdleState()
{
}

void Enemy3IdleState::Update(float deltaTime)
{
	EnemyState::Update(deltaTime);

	//change state
	if (_enemy->GetVelocity().x != 0)
	{
		_enemy->SetState(new Enemy3WalkState(_enemy));
		return;
	}

	if (_enemy->IsTargetInAttackRange())
	{
		_enemy->SetState(new Enemy3AttackState(_enemy));
		return;
	}
}
