#include "ResourceManager.h"

ResourceManager* ResourceManager::_instance = NULL;

ResourceManager::ResourceManager()
{
	Graphics* graphics = Graphics::GetInstance();

	_animationXMLAladdin = new tinyxml2::XMLDocument();
	_animationXMLAladdin->LoadFile("Resources/Aladdin/Aladdin-Animations.xml");

	_animationXMLEnemy1 = new tinyxml2::XMLDocument();
	_animationXMLEnemy1->LoadFile("Resources/Enemies/Enemy-1-Animations.xml");

	_animationXMLAppleWeapon = new tinyxml2::XMLDocument();
	_animationXMLAppleWeapon->LoadFile("Resources/Items/AppleWeapon-Animation.xml");

	_textureAladdin = graphics->LoadTexture(L"Resources/Aladdin/Aladdin_Sprite.png", D3DCOLOR_XRGB(255, 0, 255));
	_textureEnemies = graphics->LoadTexture(L"Resources/Enemies/Enemies_Sprite.png", D3DCOLOR_XRGB(120, 193, 152));
	_textureItems = graphics->LoadTexture(L"Resources/Items/Items.png", D3DCOLOR_XRGB(248, 0, 248));
	_textureAgrabahMarket = graphics->LoadTexture(L"Resources/Maps/AgrabahMarket/AgrabahMarket.png");
}


ResourceManager::~ResourceManager()
{
	_textureAladdin->Release();
	_textureEnemies->Release();
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

tinyxml2::XMLDocument * ResourceManager::GetAnimationXMLAppleWeapon()
{
	return _animationXMLAppleWeapon;
}

LPDIRECT3DTEXTURE9 ResourceManager::GetTextureAladdin()
{
	return _textureAladdin;
}

LPDIRECT3DTEXTURE9 ResourceManager::GetTextureEnemies()
{
	return _textureEnemies;
}

LPDIRECT3DTEXTURE9 ResourceManager::GetTextureItems()
{
	return _textureItems;
}

LPDIRECT3DTEXTURE9 ResourceManager::GetTextureAgrabahMarket()
{
	return _textureAgrabahMarket;
}
