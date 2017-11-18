#include "JafarAttack.h"
#include "SnakeAttack.h"
#include "Jafar.h"

JafarAttack::JafarAttack()
{

}

JafarAttack::~JafarAttack()
{

}

JafarAttack::JafarAttack(Enemy* jafar) : EnemyState(jafar, EnemyState::StateName::Jafar)
{
	SetAnimation(new Animation(ResourceManager::GetInstance()->GetAnimationXMLJafar(), "Attack", ResourceManager::GetInstance()->GetTextureBossJafar(), true, 1.5f));
	_isCreatedWeapon = false;
}

void JafarAttack::Update(float deltatime)
{
	EnemyState::Update(deltatime);

	if (_enemy->GetHealth() <= 150)//chuyen dang Snake
	{
		_enemy->SetState(new SnakeAttack(_enemy));
		return;
	}



	if (!_isCreatedWeapon && _animation->GetCurrentIndex() == 3)
	{
		_isCreatedWeapon = true;

		JafarWeapon* weapon = new JafarWeapon();


		//weapon->SetPosition(_enemy->GetPosition());

		//set position weapon when player letf of right with Jafar
		if (_enemy->GetDistanceToTarget().x <0)
		{
			weapon->SetPosition(_enemy->GetPosition().x - _enemy->GetHeight() / 2, _enemy->GetPosition().y - _enemy->GetHeight() / 2);
		}
		else if (_enemy->GetDistanceToTarget().x>0)
		{
			weapon->SetPosition(_enemy->GetPosition().x, _enemy->GetPosition().y - _enemy->GetHeight() / 2);
		}

		D3DXVECTOR2 weaponVeclocity = _enemy->GetTarget()->GetPosition() - weapon->GetPosition();
		D3DXVec2Normalize(&weaponVeclocity, &weaponVeclocity);
		weapon->SetVelocity(weaponVeclocity * 30);


		SceneManager::GetInstance()->GetCurrentScene()->AddGameObjectToWeaponList(weapon);

		QuadTree::InsertDynamicObject(weapon);


	}
	if (_animation->GetCurrentIndex() == 4)
		_isCreatedWeapon = false;
}
