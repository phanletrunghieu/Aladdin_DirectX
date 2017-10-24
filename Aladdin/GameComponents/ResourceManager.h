#pragma once

#include "Graphics.h"
#include "../TmxParser/tinyxml2/tinyxml2.h"

class ResourceManager
{
private:
	static ResourceManager *_instance;

	tinyxml2::XMLDocument  *_aladdinAnimationXML;
	tinyxml2::XMLDocument  *_appleWeaponAnimationXML;

	LPDIRECT3DTEXTURE9 _textureAladdin;
public:
	ResourceManager();
	~ResourceManager();

	static ResourceManager* GetInstance();

	tinyxml2::XMLDocument* GetAladdinAnimationXML();
	tinyxml2::XMLDocument* GetAppleWeaponAnimationXML();

	LPDIRECT3DTEXTURE9 GetAladdinTexture();
};

