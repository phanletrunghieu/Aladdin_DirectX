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
	tinyxml2::XMLDocument *_animationXMLEnemy6;
	tinyxml2::XMLDocument *_animationXMLAppleWeapon;
	tinyxml2::XMLDocument *_animationXMLCamelWeapon;
	tinyxml2::XMLDocument *_animationXMLEnemy3Weapon;
	tinyxml2::XMLDocument *_animationXMLEnemy6Weapon;
	tinyxml2::XMLDocument *_animationXMLPlayerHealthMeter;
	tinyxml2::XMLDocument *_animationXMLCamel;

	tinyxml2::XMLDocument *_animationXMLJafar;
	tinyxml2::XMLDocument *_animationXMLSnake;
	tinyxml2::XMLDocument *_animationXMLExplosions;
	tinyxml2::XMLDocument *_animationXMLJafarWeapon1;
	tinyxml2::XMLDocument *_animationXMLJafarWeapon2;

	LPDIRECT3DTEXTURE9 _textureAladdin;
	LPDIRECT3DTEXTURE9 _textureEnemies1;
	LPDIRECT3DTEXTURE9 _textureEnemies2;
	LPDIRECT3DTEXTURE9 _textureItems;
	LPDIRECT3DTEXTURE9 _textureCamel;

	//map 1
	LPDIRECT3DTEXTURE9 _textureAgrabahMarket;

	//man boss:
	LPDIRECT3DTEXTURE9 _textureBossJafar;
	LPDIRECT3DTEXTURE9 _textureExplosions;

	//map 2 TEST
	LPDIRECT3DTEXTURE9 _textureMapBoss;
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
	tinyxml2::XMLDocument* GetAnimationXMLEnemy6();
	tinyxml2::XMLDocument* GetAnimationXMLAppleWeapon();
	tinyxml2::XMLDocument* GetAnimationXMLCamelWeapon();
	tinyxml2::XMLDocument* GetAnimationXMLEnemy3Weapon();
	tinyxml2::XMLDocument* GetAnimationXMLEnemy6Weapon();
	tinyxml2::XMLDocument* GetAnimationXMLPlayerHealthMeter();
	tinyxml2::XMLDocument* GetAnimationXMLCamel();

	tinyxml2::XMLDocument* GetAnimationXMLJafar();
	tinyxml2::XMLDocument* GetAnimationXMLSnake();
	tinyxml2::XMLDocument* GetAnimationXMLExplosions();
	tinyxml2::XMLDocument* GetAnimationXMLJafarWeapon1();
	tinyxml2::XMLDocument* GetAnimationXMLJafarWeapon2();

	LPDIRECT3DTEXTURE9 GetTextureAladdin();
	LPDIRECT3DTEXTURE9 GetTextureEnemies1();
	LPDIRECT3DTEXTURE9 GetTextureEnemies2();
	LPDIRECT3DTEXTURE9 GetTextureItems();
	LPDIRECT3DTEXTURE9 GetTextureCamel();
	LPDIRECT3DTEXTURE9 GetTextureAgrabahMarket();
	LPDIRECT3DTEXTURE9 GetTextureExplosions();
	LPDIRECT3DTEXTURE9 GetTextureBossJafar();
	LPDIRECT3DTEXTURE9 GetTextureMapBoss();
};

