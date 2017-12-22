#pragma once
#include "../GameObjects/Camera.h"
#include "../GameComponents/Animation.h"
#include "../GameComponents/Text.h"
#include "../GameComponents/Scene.h"


class VictoryScene :public Scene
{

	Text* _title;
	Animation *_animationAladdin;
	Animation *_animationMonkey;
public:
	VictoryScene();
	~VictoryScene();

	void LoadContent();
	void Update(float deltatime);
	void Draw();
};