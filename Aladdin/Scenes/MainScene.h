#pragma once

#include "../GameObjects/Camera.h"
#include "../GameComponents/Sprite.h"
#include "../GameComponents/Text.h"
#include "../GameComponents/Scene.h"
#include "../GameComponents/Input.h"
#include "../GameObjects/PlayerHealthMeter.h"


class MainScene : public Scene
{
private:
	std::vector<Sprite*> _backgroundTextures;

	Text *_txtCountApple;
	Sprite *_spriteCountApple;

	Text *_txtTimesPlay;
	Sprite *_spriteTimesPlay;

	Text *_txtScore;

	PlayerHealthMeter *_playerHealthMeter;
public:
	MainScene();
	~MainScene();

	void LoadContent();
	void Update(float dt);
	void Draw();
};

