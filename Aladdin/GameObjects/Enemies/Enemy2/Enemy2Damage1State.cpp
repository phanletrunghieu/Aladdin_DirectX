#include "Enemy2Damage1State.h"
#include "Enemy2.h"
#include "Enemy2IdleState.h"

Enemy2Damage1State::Enemy2Damage1State()
{
	//not use
}

Enemy2Damage1State::Enemy2Damage1State(Enemy * enemy) : EnemyState(enemy, EnemyState::StateName::Damage)
{
	SetAnimation(new Animation(ResourceManager::GetInstance()->GetAnimationXMLEnemy2(), "Damage1", ResourceManager::GetInstance()->GetTextureEnemies1(), false, 0.8f));
}


Enemy2Damage1State::~Enemy2Damage1State()
{
}

void Enemy2Damage1State::Update(float deltaTime)
{
	EnemyState::Update(deltaTime);

	//change state
	if (_animation->IsFinish())
	{
		_enemy->SetState(new Enemy2IdleState(_enemy));
		return;
	}
}
