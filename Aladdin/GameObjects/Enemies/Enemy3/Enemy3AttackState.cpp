#include "Enemy3AttackState.h"
#include "Enemy3.h"


Enemy3AttackState::Enemy3AttackState()
{
	//not use
}

Enemy3AttackState::Enemy3AttackState(Enemy * enemy) : EnemyState(enemy, EnemyState::StateName::Attack)
{
	SetAnimation(new Animation(ResourceManager::GetInstance()->GetAnimationXMLEnemy3(), "Attack", ResourceManager::GetInstance()->GetTextureEnemies(), 1.0f));
}


Enemy3AttackState::~Enemy3AttackState()
{
}

void Enemy3AttackState::Update(float deltaTime)
{
	EnemyState::Update(deltaTime);

	//change state
	if (!_enemy->IsTargetInAttackRange() && _enemy->GetTarget()->GetVelocity().x != 0)
	{
		_enemy->SetState(new Enemy3WalkState(_enemy));
		return;
	}
}
