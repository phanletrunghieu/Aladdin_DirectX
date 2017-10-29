#include "Enemy1IdleState.h"
#include "Enemy1.h"


Enemy1IdleState::Enemy1IdleState()
{
	//not use
}

Enemy1IdleState::Enemy1IdleState(Enemy * enemy) : EnemyState(enemy, EnemyState::StateName::Idle)
{
	_animation = new Animation(ResourceManager::GetInstance()->GetAnimationXMLEnemy1(), "Idle", ResourceManager::GetInstance()->GetTextureEnemies());
	_animation->FlipHorizontal(_enemy->IsRight());

	_animation->SetPosition(_enemy->GetPosition());
	_enemy->SetWidth(_animation->GetWidth());
	_enemy->SetHeight(_animation->GetHeight());
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
