#include "Jafar.h"
#include "../../Player/Player.h"
#include "JafarAttack.h"

Jafar::Jafar()
{
	//not use
}

Jafar::~Jafar()
{
	delete _state;
}

Jafar::Jafar(GameObject * target) :Enemy(target)
{
	_health = 300;
	_isRight = false;
	_allowMoveLeft = _allowMoveRight = false;
	_state = new JafarAttack(this);
}

void Jafar::Update(float deltatime)
{
	Enemy::Update(deltatime);
}

void Jafar::Draw(Camera * camera)
{
	Animation *animation = _state->GetAnimation();
	if (animation != NULL)
		animation->Draw(camera);
}

void Jafar::OnCollision(GameObject *target, GameCollision::SideCollisions side)
{
	//khi boss va cham vs player
	if (target->GetTag() == GameObject::GameObjectType::Players)
	{
		Player *player = dynamic_cast<Player*>(target);
		if (player->GetState()->GetName() == PlayerState::StateName::Attack && !player->GetState()->IsAttackedEnemy())
		{
			_health -= player->GetDamage();
			player->GetState()->SetIsAttackedEnemy(true);
		}
	}
	//khi boss va cham vs appleWeapon
	if (target->GetTag() == GameObject::GameObjectType::Weapons)
	{
		Weapon *weapon = dynamic_cast<Weapon*>(target);
		if (weapon->GetWeaponType() == Weapon::WeaponType::PlayerWeapons)
		{
			_health -= weapon->GetDamage();
		}
	}

	_state->OnCollision(target, side);
}