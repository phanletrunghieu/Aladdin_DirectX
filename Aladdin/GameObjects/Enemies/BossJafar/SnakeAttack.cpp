#include "SnakeAttack.h"
#include "Jafar.h"

SnakeAttack::SnakeAttack()
{

}

SnakeAttack::~SnakeAttack()
{

}

SnakeAttack::SnakeAttack(Enemy* jafar) :EnemyState(jafar, EnemyState::StateName::Snake)
{
	SetAnimation(new Animation(ResourceManager::GetInstance()->GetAnimationXMLSnake(), "snake", ResourceManager::GetInstance()->GetTextureBossJafar(), true, 1.0f));
	_isCreatedWeapon = false;
}

void SnakeAttack::Update(float deltatime)
{
	EnemyState::Update(deltatime);

	if (!_isCreatedWeapon && _animation->GetCurrentIndex() == 9)
	{
		_isCreatedWeapon = true;

		SnakeWeapon* weapon = new SnakeWeapon();
		//weapon->SetPosition(_enemy->GetPosition().x, _enemy->GetPosition().y);


		weapon->SetPosition(_enemy->GetPosition().x, _enemy->GetBound().bottom - weapon->GetHeight() / 2);

		//weapon->SetVelocityX(_enemy->GetDistanceToTarget().x<0);
		weapon->SetVelocityX(weapon->GetVelocity().x * (_enemy->IsRight() ? 1 : -1));


		//

		/*D3DXVECTOR2 weaponVeclocity = _enemy->GetTarget()->GetPosition() - weapon->GetPosition();
		D3DXVec2Normalize(&weaponVeclocity, &weaponVeclocity);
		weapon->SetVelocity(weaponVeclocity * 30);*/

		SceneManager::GetInstance()->GetCurrentScene()->AddGameObjectToWeaponList(weapon);

		QuadTree::InsertDynamicObject(weapon);


	}
	if (_animation->GetCurrentIndex() == 10)
		_isCreatedWeapon = false;

}