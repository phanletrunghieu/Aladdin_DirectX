#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <d3dx9tex.h>
#include <string>

class Graphics
{
private:
	static Graphics* _instance;

	LPDIRECT3DDEVICE9 _d3dDevice;
	LPDIRECT3D9 _d3d;
	HWND _hwnd;
	HINSTANCE _hInstance;

	LPD3DXSPRITE _sprite;

	int _screenWidth;
	int _screenHeight;
	bool _isFullScreen;

	D3DFORMAT FindDepthStencilFormat(ULONG AdapterOrdinal, D3DDISPLAYMODE Mode, D3DDEVTYPE DevType);
public:
	Graphics();
	Graphics(HWND hwnd, HINSTANCE hInstance, int screenWidth, int screenHeight, bool isFullScreen = true);
	~Graphics();

	static Graphics* GetInstance();

	bool Init();
	void Release();

	LPDIRECT3DTEXTURE9 LoadTexture(LPCWSTR filePath, D3DCOLOR colorKey = NULL);

	LPDIRECT3DDEVICE9 GetDevice();
	LPDIRECT3DSURFACE9 GetBackBuffer();
	LPD3DXSPRITE GetSpriteHandler();

	HWND GetHWND();

	int GetScreenWidth();
	int GetScreenHeight();
};

