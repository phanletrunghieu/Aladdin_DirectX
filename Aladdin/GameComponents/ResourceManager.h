#pragma once

#include "Graphics.h"
#include "../TmxParser/tinyxml2/tinyxml2.h"

class ResourceManager
{
private:
	static ResourceManager *_instance;

	tinyxml2::XMLDocument  *_animationXMLAladdin;
	tinyxml2::XMLDocument  *_animationXMLEnemy1;
	tinyxml2::XMLDocument  *_animationXMLEnemy2;
	tinyxml2::XMLDocument  *_animationXMLAppleWeapon;

	LPDIRECT3DTEXTURE9 _textureAladdin;
	LPDIRECT3DTEXTURE9 _textureEnemies;
	LPDIRECT3DTEXTURE9 _textureItems;

	//map 1
	LPDIRECT3DTEXTURE9 _textureAgrabahMarket;
public:
	ResourceManager();
	~ResourceManager();

	static ResourceManager* GetInstance();

	tinyxml2::XMLDocument* GetAnimationXMLAladdin();
	tinyxml2::XMLDocument* GetAnimationXMLEnemy1();
	tinyxml2::XMLDocument* GetAnimationXMLEnemy2();
	tinyxml2::XMLDocument* GetAnimationXMLAppleWeapon();

	LPDIRECT3DTEXTURE9 GetTextureAladdin();
	LPDIRECT3DTEXTURE9 GetTextureEnemies();
	LPDIRECT3DTEXTURE9 GetTextureItems();
	LPDIRECT3DTEXTURE9 GetTextureAgrabahMarket();
};

