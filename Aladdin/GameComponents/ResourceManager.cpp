#include "ResourceManager.h"

ResourceManager* ResourceManager::_instance = NULL;

ResourceManager::ResourceManager()
{
	_animationXMLAladdin = new tinyxml2::XMLDocument();
	_animationXMLAladdin->LoadFile("Resources/Aladdin/Aladdin-Animations.xml");

	_animationXMLAppleWeapon = new tinyxml2::XMLDocument();
	_animationXMLAppleWeapon->LoadFile("Resources/Items/AppleWeapon-Animation.xml");

	_textureAladdin = Graphics::GetInstance()->LoadTexture(L"Resources/Aladdin/Aladdin_Sprite.png", D3DCOLOR_XRGB(255, 0, 255));
	_textureItems = Graphics::GetInstance()->LoadTexture(L"Resources/Items/Items.png", D3DCOLOR_XRGB(248, 0, 248));
	_textureAgrabahMarket = Graphics::GetInstance()->LoadTexture(L"Resources/Maps/AgrabahMarket/AgrabahMarket.png");
}


ResourceManager::~ResourceManager()
{
	_textureAladdin->Release();
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

tinyxml2::XMLDocument * ResourceManager::GetAnimationXMLAppleWeapon()
{
	return _animationXMLAppleWeapon;
}

LPDIRECT3DTEXTURE9 ResourceManager::GetTextureAladdin()
{
	return _textureAladdin;
}

LPDIRECT3DTEXTURE9 ResourceManager::GetTextureItems()
{
	return _textureItems;
}

LPDIRECT3DTEXTURE9 ResourceManager::GetTextureAgrabahMarket()
{
	return _textureAgrabahMarket;
}
