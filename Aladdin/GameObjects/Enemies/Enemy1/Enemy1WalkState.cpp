#include "Enemy1WalkState.h"
#include "Enemy1.h"


Enemy1WalkState::Enemy1WalkState()
{
}

Enemy1WalkState::Enemy1WalkState(Enemy * enemy) : EnemyState(enemy, EnemyState::StateName::Walk)
{
	_animation = new Animation(ResourceManager::GetInstance()->GetAnimationXMLEnemy1(), "Walk", ResourceManager::GetInstance()->GetTextureEnemies(), 0.7f);
	_animation->FlipHorizontal(_enemy->IsRight());

	_animation->SetPosition(_enemy->GetPosition());
	_enemy->SetWidth(_animation->GetWidth());
	_enemy->SetHeight(_animation->GetHeight());
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
