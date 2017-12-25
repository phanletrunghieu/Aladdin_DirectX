#include "Stair.h"
#include "../../GameComponents/SceneManager.h"


Stair::Stair(GameCollision::SideCollisions side) : GameObject(GameObject::GameObjectType::Stairs, false)
{
	_side = side;

	_allowIncreaseCounter = false;
	_countCollision = 1;
}


Stair::~Stair()
{
}

void Stair::CheckCollision()
{
	std::vector<GameObject*> listCanCollide;
	SceneManager::GetInstance()->GetCurrentScene()->GetQuadTree()->Retrieve(listCanCollide, this);

	bool collisionWithPlayer = false;

	for (size_t i = 0; i < listCanCollide.size(); i++)
	{
		GameObject *gameObject = listCanCollide.at(i);
		bool isInCamera = _camera->IsInCamera(gameObject->GetPosition(), gameObject->GetWidth(), gameObject->GetHeight());
		if (!gameObject->IsVisible() || !isInCamera)
			continue;

		//lay va cham cua other voi this
		GameCollision collisionData = GameCollision::CheckCollision(this->GetBound(), gameObject->GetBound());
		if (collisionData.IsCollided())
		{
			this->OnCollision(gameObject, collisionData.GetSide());

			if (gameObject->GetTag() == GameObject::GameObjectType::Players)
			{
				collisionWithPlayer = true;
			}
		}
	}

	if (!collisionWithPlayer)
		_allowIncreaseCounter = true;
}

void Stair::OnCollision(GameObject * target, GameCollision::SideCollisions side)
{
	if (target->GetTag() == GameObject::GameObjectType::Players
		&& (side == GameCollision::SideCollisions::Top
		|| side == GameCollision::SideCollisions::TopLeft
		|| side == GameCollision::SideCollisions::TopRight)
		&& _allowIncreaseCounter) {
		SetCounter(_countCollision + 1);
		_allowIncreaseCounter = false;
		return;
	}
}

void Stair::SetCounter(int counter)
{
	_countCollision = counter;
}

bool Stair::IsCheckCollisionAsGround()
{
	return _countCollision % 2 == 0;
}

GameCollision::SideCollisions Stair::GetSide()
{
	return _side;
}
