#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <vector>
#include <algorithm>

class GameCollision
{
public:
	enum SideCollisions
	{
		UnKnow,
		Left,
		Right,
		Top,
		Bottom,
		TopLeft,
		TopRight,
		BottomLeft,
		BottomRight
	};

	GameCollision();
	~GameCollision();

	static GameCollision CheckCollision(RECT rect1, RECT rect2);

	bool IsCollided();
	GameCollision::SideCollisions GetSide();
private:
	bool _isCollided;
	SideCollisions _side;
};