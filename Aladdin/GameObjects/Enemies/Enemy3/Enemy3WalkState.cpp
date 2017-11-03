#include "Enemy3WalkState.h"
#include "Enemy3.h"


Enemy3WalkState::Enemy3WalkState()
{
}

Enemy3WalkState::Enemy3WalkState(Enemy * enemy) : EnemyState(enemy, EnemyState::StateName::Walk)
{
	SetAnimation(new Animation(ResourceManager::GetInstance()->GetAnimationXMLEnemy3(), "Walk", ResourceManager::GetInstance()->GetTextureEnemies1(), false, 0.7f));
}


Enemy3WalkState::~Enemy3WalkState()
{
}

void Enemy3WalkState::Update(float deltaTime)
{
	EnemyState::Update(deltaTime);

	//change state
	if (_enemy->GetVelocity().x == 0)//change state
	{
		_enemy->SetState(new Enemy3IdleState(_enemy));
		return;
	}

	if (_enemy->IsTargetInAttackRange())
	{
		_enemy->SetState(new Enemy3AttackState(_enemy));
		return;
	}
}
