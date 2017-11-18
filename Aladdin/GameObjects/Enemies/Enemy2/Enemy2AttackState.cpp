#include "Enemy2AttackState.h"
#include "Enemy2.h"
#include "Enemy2WalkState.h"

Enemy2AttackState::Enemy2AttackState()
{
	//not use
}

Enemy2AttackState::Enemy2AttackState(Enemy * enemy) : EnemyState(enemy, EnemyState::StateName::Attack)
{
	_animationAttack1 = new Animation(ResourceManager::GetInstance()->GetAnimationXMLEnemy2(), "Attack1", ResourceManager::GetInstance()->GetTextureEnemies1(), false, 1.0f);
	_animationAttack2 = new Animation(ResourceManager::GetInstance()->GetAnimationXMLEnemy2(), "Attack2", ResourceManager::GetInstance()->GetTextureEnemies1(), false, 1.0f);

	SetAnimation(_animationAttack1);
}


Enemy2AttackState::~Enemy2AttackState()
{
	if (_animationAttack1)
	{
		delete _animationAttack1;
		_animationAttack1 = NULL;
	}

	if (_animationAttack2)
	{
		delete _animationAttack2;
		_animationAttack2 = NULL;
	}
}

void Enemy2AttackState::Update(float deltaTime)
{
	EnemyState::Update(deltaTime);

	//change state
	if (!_enemy->IsTargetInAttackRange() && _enemy->GetTarget()->GetVelocity().x != 0)
	{
		_enemy->SetState(new Enemy2WalkState(_enemy));
		return;
	}

	//random animation
	if (_animation->IsFinish())
	{
		int r = rand() % 10;
		if (r == 0)
		{
			if (_animation != _animationAttack1)
			{
				SetAnimation(_animationAttack1);

				//fix foot position
				float posY = _enemy->GetPosition().y;
				float diff = (_animationAttack2->GetHeight() - _animationAttack1->GetHeight()) / 2.0f;
				_enemy->SetPositionY(posY + diff);
			}
		}
		else
		{
			if (_animation != _animationAttack2)
			{
				SetAnimation(_animationAttack2);

				//fix foot position
				float posY = _enemy->GetPosition().y;
				float diff = (_animationAttack1->GetHeight() - _animationAttack2->GetHeight()) / 2.0f;
				_enemy->SetPositionY(posY + diff);
			}
		}
	}
}
