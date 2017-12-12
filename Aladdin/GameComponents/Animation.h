#pragma once

#include "Sprite.h"
#include "../TmxParser/tinyxml2/tinyxml2.h"

class Animation : public Sprite
{
protected:
	std::vector<RECT> _listRectSprites;
	std::vector<D3DXVECTOR2> _listOriginPointSprites;

	bool _paused, _isBegin, _isFinish, _loop, _isReverse;

	int _currentIndex;
	float _timePerFrame, _currentTotalTime;

	void ChangeCurrentIndex();
	void CheckIsBeginOrFinish();
public:
	Animation(tinyxml2::XMLDocument *xmlDocument, char* animationName, LPDIRECT3DTEXTURE9 texture, bool isSourceRight = true, float timePerFrame = 0.1f, bool loop = true);
	Animation();
	~Animation();

	void Update(float dt);

	void SeekToLastFrame();

	int GetCurrentIndex();
	void SetCurrentIndex(int index);

	bool IsPaused();

	bool IsBegin();
	bool IsFinish();

	bool IsLoop();
	void SetLoop(bool loop);

	void Reverse(bool reverse);
	bool IsReverse();

	void Pause();
	void Play();
};

