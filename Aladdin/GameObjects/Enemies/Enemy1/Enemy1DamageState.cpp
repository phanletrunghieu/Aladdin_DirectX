#include "Enemy1DamageState.h"
#include "Enemy1.h"


Enemy1DamageState::Enemy1DamageState()
{
	//not use
}

Enemy1DamageState::Enemy1DamageState(Enemy * enemy) : EnemyState(enemy, EnemyState::StateName::Damage)
{
	SetAnimation(new Animation(ResourceManager::GetInstance()->GetAnimationXMLEnemy1(), "Damage", ResourceManager::GetInstance()->GetTextureEnemies1(), false, 0.8f));
}


Enemy1DamageState::~Enemy1DamageState()
{
}

void Enemy1DamageState::Update(float deltaTime)
{
	EnemyState::Update(deltaTime);

	//change state
	if (_animation->IsFinish())
	{
		_enemy->SetState(new Enemy1IdleState(_enemy));
		return;
	}
}
