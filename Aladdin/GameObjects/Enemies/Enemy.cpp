#include "Enemy.h"
#include "../Player/Player.h"

Enemy::Enemy() : GameObject(GameObject::GameObjectType::Enemies, true)
{
	//not use
}

Enemy::Enemy(GameObject * target) : GameObject(GameObject::GameObjectType::Enemies)
{
	_target = target;
	_distanceToTarget = _target->GetPosition() - _position;

	_footPosY = 0;

	_health = 100;
	_damage = 5;
	_speed = 10;

	_viewRangeX = 300;
	_viewRangeY = 80;

	_attackRangeX = 80;
	_attackRangeY = 80;

	_isRight = false;
	_allowMoveLeft = _allowMoveRight = true;

	_collidedWithCoalDuration = 0;
}

Enemy::~Enemy()
{
	delete _state;
}

void Enemy::Update(float deltaTime)
{
	// calculate distance to target (player)
	_distanceToTarget = _target->GetPosition() - _position;

	//check isDie
	if (_health <= 0)
		_isVisible = false;

	//face to left or right
	if(_distanceToTarget.x > 0)
		_isRight = true;
	else if (_distanceToTarget.x < 0)
		_isRight = false;

	//move
	if(IsTargetInViewRange() && !IsTargetInAttackRange())
	{
		if (_distanceToTarget.x > 0 && _allowMoveRight)
		{
			//move right
			_velocity.x = _speed;
		}
		else if(_distanceToTarget.x < 0 && _allowMoveLeft)
		{
			//move left
			_velocity.x = -1 * _speed;
		}
	}
	else
	{
		//v=0
		_velocity.x = 0;
	}

	GameObject::Update(deltaTime);
	_state->Update(deltaTime);

	//fix foot posY
	_position.y = _footPosY - _height / 2;
}

void Enemy::Draw(Camera * camera)
{
	Animation *animation = _state->GetAnimation();
	if (animation != NULL)
		animation->Draw(camera);
}

void Enemy::OnCollision(GameObject * target, GameCollision::SideCollisions side)
{
	if (target->GetTag() == GameObject::GameObjectType::Players)
	{
		Player *player = dynamic_cast<Player*>(target);
		
		if (player->GetState()->GetName() == PlayerState::StateName::Attack && !player->GetState()->IsAttackedEnemy())
		{
			_health -= player->GetDamage();
			player->GetState()->SetIsAttackedEnemy(true);
		}
	}

	if (target->GetTag() == GameObject::GameObjectType::Weapons)
	{
		Weapon* weapon = dynamic_cast<Weapon*>(target);
		if (weapon->GetWeaponType() == Weapon::WeaponType::PlayerWeapons)
		{
			_health -= weapon->GetDamage();
		}
	}
	
	if (target->GetTag() == GameObject::GameObjectType::Coal)
	{
		//when colliding with coal, each duration, player's health will decrease
		_collidedWithCoalDuration += _deltaTime;
		if (_collidedWithCoalDuration >= 3)
		{
			_collidedWithCoalDuration = 0;
			SetHealth(_health - 10);
		}
	}
	
	_state->OnCollision(target, side);
}

bool Enemy::IsTargetInViewRange()
{
	if (abs(_distanceToTarget.x) <= _viewRangeX && abs(_distanceToTarget.y) < _viewRangeY)
		return true;
	return false;
}

bool Enemy::IsTargetInAttackRange()
{
	if (abs(_distanceToTarget.x) <= _attackRangeX && abs(_distanceToTarget.y) < _attackRangeY)
		return true;
	return false;
}

void Enemy::SetFootPosY()
{
	if (_footPosY == 0)
		_footPosY = _position.y + _height / 2;
}

EnemyState * Enemy::GetState()
{
	return _state;
}

void Enemy::SetState(EnemyState * state, bool fixFootPosition)
{
	if (fixFootPosition)
	{
		//make sure enemy's foot at the same position when change state. because each state has own height
		int newHeight = state->GetAnimation()->GetHeight();
		int currentHeight = _state->GetAnimation()->GetHeight();
		float diff = (currentHeight - newHeight) / 2.0;
		_position.y += diff;
	}

	//change state
	delete _state;
	_state = state;
}

GameObject * Enemy::GetTarget()
{
	return _target;
}

int Enemy::GetHealth()
{
	return _health;
}

void Enemy::SetHealth(int newHealth)
{
	_health = newHealth;
}

int Enemy::GetDamage()
{
	return _damage;
}

void Enemy::SetDamage(int newDamage)
{
	_damage = newDamage;
}

bool Enemy::IsRight()
{
	return _isRight;
}

void Enemy::SetIsRight(bool right)
{
	_isRight = right;

	if (_state->GetAnimation()->IsSourceRight())
		_state->GetAnimation()->FlipHorizontal(!_isRight);
	else
		_state->GetAnimation()->FlipHorizontal(_isRight);
}

bool Enemy::IsAllowMoveLeft()
{
	return _allowMoveLeft;
}

bool Enemy::IsAllowMoveRight()
{
	return _allowMoveRight;
}

void Enemy::AllowMoveLeft(bool allow)
{
	_allowMoveLeft = allow;
}

void Enemy::AllowMoveRight(bool allow)
{
	_allowMoveRight = allow;
}

void Enemy::SetPosition(float x, float y)
{
	GameObject::SetPosition(x, y);
	SetFootPosY();
}

void Enemy::SetPosition(D3DXVECTOR2 position)
{
	GameObject::SetPosition(position);
	SetFootPosY();
}

void Enemy::SetPosition(D3DXVECTOR3 position)
{
	GameObject::SetPosition(position);
	SetFootPosY();
}
