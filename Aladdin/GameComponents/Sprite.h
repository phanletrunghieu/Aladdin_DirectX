#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "Graphics.h"
#include "../GameObjects/Camera.h"

class Sprite
{
protected:
	LPDIRECT3DTEXTURE9 _texture; // load hinh anh vao day
	LPD3DXSPRITE _spriteHandler; //SpriteHandler ho tro ve hinh
	D3DXIMAGE_INFO _imageInfo; // thong tin thuc cua hinh anh duoc lay
	RECT _sourceRect; // hinh chu nhat cat tu anh cua texture

	int _width, _height; // kich thuoc cua texture
	bool _isFlipVertical, _isFlipHorizontal;

	D3DXVECTOR3 _position;
	D3DXVECTOR2 _scale;
	D3DXVECTOR2 _translation;
	D3DXMATRIX _matrix;
	D3DXVECTOR2 _rotationCenter;
	float _rotation;// radian

	bool IsRect(RECT rect);
public:
	//Sprite(LPCWSTR filePath, D3DCOLOR colorKey = NULL, RECT sourceRect = RECT(), int width = NULL, int height = NULL);
	Sprite(LPDIRECT3DTEXTURE9 texture, RECT sourceRect = RECT(), int width = NULL, int height = NULL);
	Sprite();
	~Sprite();

	void Draw(Camera* camera);
	void Draw(D3DXVECTOR3 position = D3DXVECTOR3());

	LPDIRECT3DTEXTURE9 GetTexture();
	D3DXIMAGE_INFO GetImageInfo(); // lay thong tin thuc cua hinh anh duoc lay

	void SetSourceRect(RECT rect);
	RECT GetSourceRect();

	void SetWidth(int width);
	int GetWidth();

	void SetHeight(int height);
	int GetHeight();

	D3DXVECTOR3 GetPosition();
	void SetPosition(D3DXVECTOR3 pos);
	void SetPosition(float x, float y);
	void SetPosition(D3DXVECTOR2 pos);

	D3DXVECTOR2 GetScale();
	void SetScale(D3DXVECTOR2 scale);

	D3DXVECTOR2 GetRotationCenter();
	void SetRotationCenter(D3DXVECTOR2 rotationCenter);

	float GetRotation();
	void SetRotation(float rotation); // by radian

	void FlipHorizontal(bool flag); // true: lat hinh theo chieu doc, false: binh thuong
	bool IsFlipHorizontal();

	void FlipVertical(bool flag); // true: lat hinh theo chieu ngang, false: binh thuong
	bool IsFlipVertical();
};

