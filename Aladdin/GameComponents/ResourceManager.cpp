#include "ResourceManager.h"

ResourceManager* ResourceManager::_instance = NULL;

ResourceManager::ResourceManager()
{
	_aladdinAnimationXML = new tinyxml2::XMLDocument();
	_aladdinAnimationXML->LoadFile("Resources/Aladdin/Aladdin-Animations.xml");

	_appleWeaponAnimationXML = new tinyxml2::XMLDocument();
	_appleWeaponAnimationXML->LoadFile("Resources/Items/AppleWeapon-Animation.xml");

	_textureAladdin = Graphics::GetInstance()->LoadTexture(L"Resources/Aladdin/Aladdin_Sprite.png", D3DCOLOR_XRGB(255, 0, 255));
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

tinyxml2::XMLDocument* ResourceManager::GetAladdinAnimationXML()
{
	return _aladdinAnimationXML;
}

tinyxml2::XMLDocument * ResourceManager::GetAppleWeaponAnimationXML()
{
	return _appleWeaponAnimationXML;
}

LPDIRECT3DTEXTURE9 ResourceManager::GetAladdinTexture()
{
	return _textureAladdin;
}
