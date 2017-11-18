
#include "../GameObjects/Camera.h"
#include "../GameComponents/Sprite.h"
#include "../GameComponents/Text.h"
#include "../GameComponents/Scene.h"
#include "../GameComponents/Input.h"
#include "../GameObjects/PlayerHealthMeter.h"

class JafarScene :public Scene
{
	std::vector<Sprite*> _backgroundTextures;

	Text* _txtCountApple;
	Sprite* _spriteCountApple;
	PlayerHealthMeter* _playHealthMeter;
public:
	JafarScene();
	~JafarScene();

	void LoadContent();
	void Update(float deltatime);
	void Draw();


};