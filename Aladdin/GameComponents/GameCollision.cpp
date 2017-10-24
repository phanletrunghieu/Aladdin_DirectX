#include "GameCollision.h"

GameCollision::GameCollision()
{
}

GameCollision::~GameCollision()
{
}

GameCollision GameCollision::CheckCollision(RECT rect1, RECT rect2)
{
	GameCollision gameCollision;

	RECT intersect;
	bool isIntersect = IntersectRect(&intersect, &rect1, &rect2);
	if(!isIntersect)
	{
		gameCollision._isCollided = false;
	}
	else
	{
		//collide
		gameCollision._isCollided = true;

		float xCenterCollisionRegion = intersect.left + (intersect.right - intersect.left) / 2.0f;
		float yCenterCollisionRegion = intersect.top + (intersect.bottom - intersect.top) / 2.0f;

		float xCenter1 = rect1.left + (rect1.right - rect1.left) / 2.0f;
		float yCenter1 = rect1.top + (rect1.bottom - rect1.top) / 2.0f;

		D3DXVECTOR2 centerCollisionRegion = D3DXVECTOR2(xCenterCollisionRegion, yCenterCollisionRegion);
		D3DXVECTOR2 centerRect1 = D3DXVECTOR2(xCenter1, yCenter1);

		//vector noi tam Rect va Collision Region
		D3DXVECTOR2 vec = centerCollisionRegion - centerRect1;

		//chuan hoa vector
		D3DXVec2Normalize(&vec, &vec);

		/*
		- neu vec.y > 0 => rect1 nam phia ben tren rect2
		- neu vec.y < 0 => rect1 nam phia ben duoi rect2
		- neu vec.x > 0 => rect1 nam phia ben phai rect2
		- neu vec.x < 0 => rect1 nam phia ben trai rect2
		*/

		//get side collision
		gameCollision._side = GameCollision::SideCollisions::UnKnow;
		if (vec.y < 0)
		{
			//collision top

			if (vec.x >= 0.8f)
			{
				//goc trong khoang 0 -> 35
				gameCollision._side = GameCollision::SideCollisions::Right;
			}
			else if (vec.x > 0.35f && vec.x < 0.8f)
			{
				//goc trong khoang 35 -> 70
				gameCollision._side = GameCollision::SideCollisions::TopRight;
			}
			else if (vec.x <= 0.35f && vec.x >= -0.35f)
			{
				//goc trong khoang 70 -> 110
				gameCollision._side = GameCollision::SideCollisions::Top;
			}
			else if (vec.x < -0.35f && vec.x >= -0.8f)
			{
				//goc trong khoang 110 -> 145
				gameCollision._side = GameCollision::SideCollisions::TopLeft;
			}
			else
			{
				//goc trong khoang 145 -> 180
				gameCollision._side = GameCollision::SideCollisions::Left;
			}
		}
		else
		{
			//collision bottom

			if (vec.x >= 0.8)
			{
				//goc trong khoang 0 -> -35
				gameCollision._side = GameCollision::SideCollisions::Right;
			}
			else if (vec.x > 0.35 && vec.x < 0.8)
			{
				//goc trong khoang -35 -> -70
				gameCollision._side = GameCollision::SideCollisions::BottomRight;
			}
			else if (vec.x <= 0.35f && vec.x >= -0.35)
			{
				//goc trong khoang -70 -> -110
				gameCollision._side = GameCollision::SideCollisions::Bottom;
			}
			else if (vec.x < -0.35f && vec.x > -0.8f)
			{
				//goc trong khoang -110 -> -145
				gameCollision._side = GameCollision::SideCollisions::BottomLeft;
			}
			else
			{
				//goc trong khoang -145 -> -180
				gameCollision._side = GameCollision::SideCollisions::Left;
			}
		}
	}

	return gameCollision;
}

bool GameCollision::IsCollided()
{
	return _isCollided;
}

GameCollision::SideCollisions GameCollision::GetSide()
{
	return _side;
}