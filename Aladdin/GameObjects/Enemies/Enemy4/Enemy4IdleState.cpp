#include "Enemy4IdleState.h"
#include "Enemy4.h"


Enemy4IdleState::Enemy4IdleState()
{
	//not use
}

Enemy4IdleState::Enemy4IdleState(Enemy * enemy) : EnemyState(enemy, EnemyState::StateName::Idle)
{
	SetAnimation(new Animation(ResourceManager::GetInstance()->GetAnimationXMLEnemy4(), "Idle", ResourceManager::GetInstance()->GetTextureEnemies2(), true, 0.5f));
}


Enemy4IdleState::~Enemy4IdleState()
{
}
