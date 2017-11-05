#pragma once

#include "Graphics.h"
#include "../TmxParser/tinyxml2/tinyxml2.h"

class ResourceManager
{
private:
	static ResourceManager *_instance;

	tinyxml2::XMLDocument *_animationXMLAladdin;
	tinyxml2::XMLDocument *_animationXMLEnemy1;
	tinyxml2::XMLDocument *_animationXMLEnemy2;
	tinyxml2::XMLDocument *_animationXMLEnemy3;
	tinyxml2::XMLDocument *_animationXMLEnemy4;
	tinyxml2::XMLDocument *_animationXMLEnemy5;
	tinyxml2::XMLDocument *_animationXMLAppleWeapon;
	tinyxml2::XMLDocument *_animationXMLPlayerHealthMeter;
	tinyxml2::XMLDocument *_animationXMLCamel;

	LPDIRECT3DTEXTURE9 _textureAladdin;
	LPDIRECT3DTEXTURE9 _textureEnemies1;
	LPDIRECT3DTEXTURE9 _textureEnemies2;
	LPDIRECT3DTEXTURE9 _textureItems;
	LPDIRECT3DTEXTURE9 _textureCamel;

	//map 1
	LPDIRECT3DTEXTURE9 _textureAgrabahMarket;
public:
	ResourceManager();
	~ResourceManager();

	static ResourceManager* GetInstance();

	tinyxml2::XMLDocument* GetAnimationXMLAladdin();
	tinyxml2::XMLDocument* GetAnimationXMLEnemy1();
	tinyxml2::XMLDocument* GetAnimationXMLEnemy2();
	tinyxml2::XMLDocument* GetAnimationXMLEnemy3();
	tinyxml2::XMLDocument* GetAnimationXMLEnemy4();
	tinyxml2::XMLDocument* GetAnimationXMLEnemy5();
	tinyxml2::XMLDocument* GetAnimationXMLAppleWeapon();
	tinyxml2::XMLDocument* GetAnimationXMLPlayerHealthMeter();
	tinyxml2::XMLDocument* GetAnimationXMLCamel();

	LPDIRECT3DTEXTURE9 GetTextureAladdin();
	LPDIRECT3DTEXTURE9 GetTextureEnemies1();
	LPDIRECT3DTEXTURE9 GetTextureEnemies2();
	LPDIRECT3DTEXTURE9 GetTextureItems();
	LPDIRECT3DTEXTURE9 GetTextureCamel();
	LPDIRECT3DTEXTURE9 GetTextureAgrabahMarket();
};

