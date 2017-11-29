#include "Animation.h"

Animation::Animation()
{
	//don't use
}

Animation::Animation(tinyxml2::XMLDocument *xmlDocument, char* animationName, LPDIRECT3DTEXTURE9 texture, bool isSourceRight, float timePerFrame, bool loop):Sprite(texture, isSourceRight)
{
	tinyxml2::XMLNode *rootNode = xmlDocument->FirstChildElement("Animations");
	tinyxml2::XMLNode *animationNode = rootNode->FirstChild();
	while (animationNode)
	{
		tinyxml2::XMLElement* animationElement = animationNode->ToElement();

		std::string nameAnimation = animationElement->Attribute("name");
		if (nameAnimation.compare(animationName) == 0)//find animation
		{
			//count frames
			tinyxml2::XMLElement *elem = animationElement->FirstChildElement();
			while (elem)
			{
				//create rect from xml
				RECT rect;
				rect.left = elem->IntAttribute("x");
				rect.right = rect.left + elem->IntAttribute("w");
				rect.top = elem->IntAttribute("y");
				rect.bottom = rect.top + elem->IntAttribute("h");
				//store rect
				_listRectSprites.push_back(rect);

				//get origin point
				int oX = elem->IntAttribute("oX");
				int oY = elem->IntAttribute("oY");
				D3DXVECTOR2 oPoint;
				oPoint.x = oX < 0 ? 0 : oX - (rect.left + (rect.right - rect.left) / 2);
				oPoint.y = oY < 0 ? 0 : oY - (rect.top + (rect.bottom - rect.top) / 2);
				_listOriginPointSprites.push_back(oPoint);

				//next
				elem = elem->NextSiblingElement();
			}
			break;
		}

		animationNode = animationNode->NextSibling();
	}

	//set width, height
	_width = _listRectSprites[_currentIndex].right - _listRectSprites[_currentIndex].left;
	_height = _listRectSprites[_currentIndex].bottom - _listRectSprites[_currentIndex].top;

	//set RECT
	_sourceRect = _listRectSprites[_currentIndex];

	_timePerFrame = timePerFrame;
	_currentIndex = 0;
	_currentTotalTime = 0;

	_paused = false;
	_isFinish = false;
	_loop = loop;
	_isReverse = false;
}

Animation::~Animation()
{

}

void Animation::ChangeCurrentIndex()
{
	//change index
	if (!_isReverse)
	{
		_currentIndex = (_currentIndex + 1) % _listRectSprites.size();
	}
	else
	{
		_currentIndex--;
		if (_currentIndex < 0)
			_currentIndex = _listRectSprites.size() - 1;
	}
}

void Animation::CheckIsBeginOrFinish()
{
	_isFinish = _currentIndex == _listRectSprites.size() - 1;
	_isBegin = _currentIndex == 0;
}

void Animation::Update(float dt)
{
	if (_listRectSprites.size() <= 1 || _paused)
		return;

	if (_currentTotalTime >= _timePerFrame)
	{
		_currentTotalTime = 0;

		ChangeCurrentIndex();

		CheckIsBeginOrFinish();

		if(_isFinish && !_loop)
			_paused = true;

		//set width, height
		_width = _listRectSprites[_currentIndex].right - _listRectSprites[_currentIndex].left;
		_height = _listRectSprites[_currentIndex].bottom - _listRectSprites[_currentIndex].top;

		//change position
		D3DXVECTOR2 vector;
		if (!_isReverse)
		{
			if (_currentIndex == 0)
				vector = _listOriginPointSprites[_currentIndex] - _listOriginPointSprites[_listOriginPointSprites.size() - 1];
			else
				vector = _listOriginPointSprites[_currentIndex] - _listOriginPointSprites[_currentIndex - 1];

		}
		else
		{
			if (_currentIndex == _listOriginPointSprites.size() - 1)
				vector = _listOriginPointSprites[_currentIndex] - _listOriginPointSprites[0];
			else
				vector = _listOriginPointSprites[_currentIndex] - _listOriginPointSprites[_currentIndex + 1];

		}

		if (!_isFlipHorizontal)
		{
			_position.x -= vector.x;
			_position.y -= vector.y;
		}
		else
		{
			_position.x += vector.x;
			_position.y -= vector.y;
		}

		//set RECT
		_sourceRect = _listRectSprites[_currentIndex];
	}
	else
	{
		_currentTotalTime += dt;
	}
}

void Animation::SeekToLastFrame()
{
	_currentIndex = _listRectSprites.size() - 2;
}

int Animation::GetCurrentIndex()
{
	return _currentIndex;
}

void Animation::SetCurrentIndex(int index)
{
	_currentIndex = index;

	if (_currentIndex >= _listRectSprites.size())
		_currentIndex = _listRectSprites.size() - 1;

	if (_currentIndex < 0)
		_currentIndex = 0;

	CheckIsBeginOrFinish();
}

bool Animation::IsBegin()
{
	return _isBegin;
}

bool Animation::IsFinish()
{
	return _isFinish;
}

bool Animation::IsLoop()
{
	return _loop;
}

void Animation::SetLoop(bool loop)
{
	_loop = loop;
}

void Animation::Reverse(bool reverse)
{
	_isReverse = reverse;
}

bool Animation::IsReverse()
{
	return _isReverse;
}

void Animation::Pause()
{
	_paused = true;
}

void Animation::Play()
{
	_paused = false;
	ChangeCurrentIndex();
	CheckIsBeginOrFinish();
}
