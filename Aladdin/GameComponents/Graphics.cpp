#include "Graphics.h"

Graphics* Graphics::_instance = NULL;

Graphics::Graphics()
{
	this->_d3d = NULL;
	this->_d3dDevice = NULL;
	this->_screenWidth = 800;
	this->_screenHeight = 600;
	this->_isFullScreen = true;

	this->_instance = this;
}

Graphics::Graphics(HWND hwnd, HINSTANCE hInstance, int screenWidth, int screenHeight, bool isFullScreen)
{
	this->_hwnd = hwnd;
	this->_hInstance = hInstance;
	this->_d3d = NULL;
	this->_d3dDevice = NULL;
	this->_screenWidth = screenWidth;
	this->_screenHeight = screenHeight;
	this->_isFullScreen = isFullScreen;

	this->_instance = this;
}

Graphics::~Graphics()
{
	Release();
}

Graphics * Graphics::GetInstance()
{
	return _instance;
}

D3DFORMAT Graphics::FindDepthStencilFormat(ULONG AdapterOrdinal, D3DDISPLAYMODE Mode, D3DDEVTYPE DevType)
{
	// Check 32bit depth buffer available
	if (SUCCEEDED(_d3d->CheckDeviceFormat(AdapterOrdinal, DevType, Mode.Format, D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_SURFACE, D3DFMT_D32)))
		if (SUCCEEDED(_d3d->CheckDepthStencilMatch(AdapterOrdinal, DevType, Mode.Format, Mode.Format, D3DFMT_D32)))
			return D3DFMT_D32;

	// Check 24bit depth buffer available
	if (SUCCEEDED(_d3d->CheckDeviceFormat(AdapterOrdinal, DevType, Mode.Format, D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_SURFACE, D3DFMT_D24X8)))
		if (SUCCEEDED(_d3d->CheckDepthStencilMatch(AdapterOrdinal, DevType, Mode.Format, Mode.Format, D3DFMT_D24X8)))
			return D3DFMT_D24X8;

	// Check 24bit depth buffer available
	if (SUCCEEDED(_d3d->CheckDeviceFormat(AdapterOrdinal, DevType, Mode.Format, D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_SURFACE, D3DFMT_D16)))
		if (SUCCEEDED(_d3d->CheckDepthStencilMatch(AdapterOrdinal, DevType, Mode.Format, Mode.Format, D3DFMT_D16)))
			return D3DFMT_D16;
	// No depth buffer supported

	return D3DFMT_UNKNOWN;
}

bool Graphics::Init()
{
	D3DPRESENT_PARAMETERS present;
	D3DDISPLAYMODE currentMode;

	if ((this->_d3d = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
		return false;
	ZeroMemory(&present, sizeof(present));

	this->_d3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &currentMode);

	present.SwapEffect = D3DSWAPEFFECT_DISCARD;
	present.Windowed = !this->_isFullScreen;
	present.AutoDepthStencilFormat = this->FindDepthStencilFormat(D3DADAPTER_DEFAULT, currentMode, D3DDEVTYPE_HAL);
	present.EnableAutoDepthStencil = true;
	present.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	present.BackBufferCount = 1;
	present.BackBufferWidth = this->_screenWidth;
	present.BackBufferHeight = this->_screenHeight;
	present.BackBufferFormat = D3DFMT_A8R8G8B8;
	present.hDeviceWindow = this->_hwnd;

	unsigned long ulFlag = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	D3DCAPS9 caps;

	ZeroMemory(&caps, sizeof(D3DCAPS9));
	this->_d3d->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);

	if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		ulFlag = D3DCREATE_HARDWARE_VERTEXPROCESSING;

	if (FAILED(this->_d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, this->_hwnd, ulFlag, &present, &this->_d3dDevice)))
	{
		ulFlag = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

		// Check if Hardware T&L is available
		this->_d3d->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, &caps);
		if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
			ulFlag = D3DCREATE_HARDWARE_VERTEXPROCESSING;

		// Attempt to Create a REF Device
		if (FAILED(this->_d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, this->_hwnd, ulFlag, &present, &this->_d3dDevice)))
			return false;
	}

	D3DXCreateSprite(this->_d3dDevice, &this->_sprite);

	if (this->_sprite == NULL)
		return false;

	return true;
}

void Graphics::Release()
{
	if (this->_d3dDevice != NULL)
	{
		this->_d3dDevice->Release();
		this->_d3dDevice = NULL;
	}

	if (this->_d3d != NULL)
	{
		this->_d3d->Release();
		this->_d3d = NULL;
	}
}

LPDIRECT3DTEXTURE9 Graphics::LoadTexture(LPCWSTR filePath, D3DCOLOR colorKey)
{
	LPDIRECT3DTEXTURE9 texture;
	D3DXIMAGE_INFO imageInfo;
	D3DXGetImageInfoFromFile(filePath, &imageInfo);

	D3DXCreateTextureFromFileEx(
		_d3dDevice,
		filePath,
		imageInfo.Width,
		imageInfo.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		colorKey,
		&imageInfo,
		NULL,
		&texture);

	return texture;
}

LPDIRECT3DDEVICE9 Graphics::GetDevice()
{
	return this->_d3dDevice;
}

LPDIRECT3DSURFACE9 Graphics::GetBackBuffer()
{
	LPDIRECT3DSURFACE9 backBuffer;
	HRESULT hr;

	if (this->_d3dDevice == NULL)
		return NULL;

	hr = this->_d3dDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backBuffer);

	if (FAILED(hr))
		return NULL;

	return backBuffer;
}

LPD3DXSPRITE Graphics::GetSpriteHandler()
{
	return _sprite;
}

HWND Graphics::GetHWND()
{
	return _hwnd;
}

int Graphics::GetScreenWidth()
{
	return _screenWidth;
}

int Graphics::GetScreenHeight()
{
	return _screenHeight;
}
