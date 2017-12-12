#include "ScoreObject2.h"



ScoreObject2::ScoreObject2(int score) : ScoreObject(score)
{
	RECT rect;
	rect.left = 343;
	rect.right = 362;
	rect.top = 171;
	rect.bottom = 195;
	_sprite = new Sprite(ResourceManager::GetInstance()->GetTextureItems(), true, rect);
	_width = _sprite->GetWidth();
	_height = _sprite->GetHeight();
}


ScoreObject2::~ScoreObject2()
{
	delete _sprite;
}

void ScoreObject2::Draw(Camera * camera)
{
	if (_isVisible)
	{
		_sprite->SetPosition(_position);
		_sprite->Draw(camera);
	}
}
