#pragma once
#include "../GameObjects/Camera.h"
#include "../GameComponents/Animation.h"
#include "../GameComponents/Text.h"
#include "../GameComponents/Scene.h"


class DefeatScene :public Scene
{

	Text* _title;
	Animation *_animationAladdin;
	
public:
	DefeatScene();
	~DefeatScene();

	void LoadContent();
	void Update(float deltatime);
	void Draw();
};