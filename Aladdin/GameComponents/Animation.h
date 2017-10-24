#pragma once

#include "Sprite.h"
#include "../TmxParser/tinyxml2/tinyxml2.h"

class Animation : public Sprite
{
protected:

	std::vector<RECT> _listRectSprites;

	bool _paused, _isBegin, _isFinish, _loop, _isReverse;

	int _currentIndex;
	float _timePerFrame, _currentTotalTime;
public:
	Animation(tinyxml2::XMLDocument *xmlDocument, char* animationName, LPDIRECT3DTEXTURE9 texture, float timePerFrame = 0.1f, bool loop = true);
	Animation();
	~Animation();

	void Update(float dt);

	void Draw(D3DXVECTOR3 position = D3DXVECTOR3());
	void Draw(Camera* camera);

	void SeekToLastFrame();

	int GetCurrentIndex();

	bool IsBegin();
	bool IsFinish();

	bool IsLoop();
	void SetLoop(bool loop);

	void Reverse(bool reverse);
	bool IsReverse();

	void Pause();
	void Play();
};

