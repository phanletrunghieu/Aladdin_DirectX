#include "ScoreObject1.h"



ScoreObject1::ScoreObject1(int score) : ScoreObject(score)
{
	RECT floatGroundSourceRect;
	floatGroundSourceRect.left = 335;
	floatGroundSourceRect.right = 373;
	floatGroundSourceRect.top = 45;
	floatGroundSourceRect.bottom = 95;
	_sprite = new Sprite(ResourceManager::GetInstance()->GetTextureItems(), true, floatGroundSourceRect);
	_width = _sprite->GetWidth();
	_height = _sprite->GetHeight();
}


ScoreObject1::~ScoreObject1()
{
	delete _sprite;
}

void ScoreObject1::Draw(Camera * camera)
{
	if (_isVisible)
	{
		_sprite->SetPosition(_position);
		_sprite->Draw(camera);
	}
}
