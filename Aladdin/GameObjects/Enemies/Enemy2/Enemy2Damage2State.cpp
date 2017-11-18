#include "Enemy2Damage2State.h"
#include "Enemy2.h"
#include "Enemy2IdleState.h"


Enemy2Damage2State::Enemy2Damage2State()
{
	//not use
}

Enemy2Damage2State::Enemy2Damage2State(Enemy * enemy) : EnemyState(enemy, EnemyState::StateName::Damage)
{
	SetAnimation(new Animation(ResourceManager::GetInstance()->GetAnimationXMLEnemy2(), "Damage2", ResourceManager::GetInstance()->GetTextureEnemies1(), false, 0.8f));
}


Enemy2Damage2State::~Enemy2Damage2State()
{
}

void Enemy2Damage2State::Update(float deltaTime)
{
	EnemyState::Update(deltaTime);

	//change state
	if (_animation->IsFinish())
	{
		_enemy->SetState(new Enemy2IdleState(_enemy));
		return;
	}
}
