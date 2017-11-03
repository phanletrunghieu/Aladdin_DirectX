#include "ResourceManager.h"

ResourceManager* ResourceManager::_instance = NULL;

ResourceManager::ResourceManager()
{
	Graphics* graphics = Graphics::GetInstance();

	_animationXMLAladdin = new tinyxml2::XMLDocument();
	_animationXMLAladdin->LoadFile("Resources/Aladdin/Aladdin-Animations.xml");

	_animationXMLEnemy1 = new tinyxml2::XMLDocument();
	_animationXMLEnemy1->LoadFile("Resources/Enemies/Enemy-1-Animations.xml");

	_animationXMLEnemy2 = new tinyxml2::XMLDocument();
	_animationXMLEnemy2->LoadFile("Resources/Enemies/Enemy-2-Animations.xml");

	_animationXMLEnemy3 = new tinyxml2::XMLDocument();
	_animationXMLEnemy3->LoadFile("Resources/Enemies/Enemy-3-Animations.xml");

	_animationXMLEnemy4 = new tinyxml2::XMLDocument();
	_animationXMLEnemy4->LoadFile("Resources/Enemies/Enemy-4-Animations.xml");

	_animationXMLEnemy5 = new tinyxml2::XMLDocument();
	_animationXMLEnemy5->LoadFile("Resources/Enemies/Enemy-5-Animations.xml");

	_animationXMLAppleWeapon = new tinyxml2::XMLDocument();
	_animationXMLAppleWeapon->LoadFile("Resources/Items/AppleWeapon-Animation.xml");

	_textureAladdin = graphics->LoadTexture(L"Resources/Aladdin/Aladdin_Sprite.png", D3DCOLOR_XRGB(255, 0, 255));
	_textureEnemies1 = graphics->LoadTexture(L"Resources/Enemies/Enemies_Sprite_1.png", D3DCOLOR_XRGB(120, 193, 152));
	_textureEnemies2 = graphics->LoadTexture(L"Resources/Enemies/Enemies_Sprite_2.png", D3DCOLOR_XRGB(120, 193, 152));
	_textureItems = graphics->LoadTexture(L"Resources/Items/Items.png", D3DCOLOR_XRGB(248, 0, 248));
	_textureAgrabahMarket = graphics->LoadTexture(L"Resources/Maps/AgrabahMarket/AgrabahMarket.png");
}


ResourceManager::~ResourceManager()
{
	delete _animationXMLAladdin;
	delete _animationXMLEnemy1;
	delete _animationXMLEnemy2;
	delete _animationXMLEnemy3;
	delete _animationXMLEnemy4;
	delete _animationXMLEnemy5;
	delete _animationXMLAppleWeapon;

	_textureAladdin->Release();
	_textureEnemies1->Release();
	_textureEnemies2->Release();
	_textureItems->Release();
	_textureAgrabahMarket->Release();
}


ResourceManager* ResourceManager::GetInstance()
{
	if (!_instance)
		_instance = new ResourceManager();
	return _instance;
}

tinyxml2::XMLDocument* ResourceManager::GetAnimationXMLAladdin()
{
	return _animationXMLAladdin;
}

tinyxml2::XMLDocument * ResourceManager::GetAnimationXMLEnemy1()
{
	return _animationXMLEnemy1;
}

tinyxml2::XMLDocument * ResourceManager::GetAnimationXMLEnemy2()
{
	return _animationXMLEnemy2;
}

tinyxml2::XMLDocument * ResourceManager::GetAnimationXMLEnemy3()
{
	return _animationXMLEnemy3;
}

tinyxml2::XMLDocument * ResourceManager::GetAnimationXMLEnemy4()
{
	return _animationXMLEnemy4;
}

tinyxml2::XMLDocument * ResourceManager::GetAnimationXMLEnemy5()
{
	return _animationXMLEnemy5;
}

tinyxml2::XMLDocument * ResourceManager::GetAnimationXMLAppleWeapon()
{
	return _animationXMLAppleWeapon;
}

LPDIRECT3DTEXTURE9 ResourceManager::GetTextureAladdin()
{
	return _textureAladdin;
}

LPDIRECT3DTEXTURE9 ResourceManager::GetTextureEnemies1()
{
	return _textureEnemies1;
}

LPDIRECT3DTEXTURE9 ResourceManager::GetTextureEnemies2()
{
	return _textureEnemies2;
}

LPDIRECT3DTEXTURE9 ResourceManager::GetTextureItems()
{
	return _textureItems;
}

LPDIRECT3DTEXTURE9 ResourceManager::GetTextureAgrabahMarket()
{
	return _textureAgrabahMarket;
}
