#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "Graphics.h"

class Text
{
private:
	LPD3DXSPRITE _spriteHandler; //SpriteHandler ho tro ve hinh

	std::wstring _string;
	LPCWSTR _fontName;
	unsigned int _width, _height, _weight;
	bool _italic;
	DWORD _alignment;//DT_CENTER, DT_LEFT, DT_RIGHT, DT_WORDBREAK, DT_EXPANDTABS, DT_NOCLIP
	D3DCOLOR _color;

	LPD3DXFONT _font;
public:
	Text();
	Text(std::wstring str, unsigned int width, unsigned height, unsigned int weight = FW_NORMAL, bool italic = false, DWORD alignment = DT_LEFT | DT_EXPANDTABS | DT_NOCLIP, D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255), LPCWSTR fontName = L"Arial");
	~Text();

	void Draw(D3DXVECTOR2 position);

	std::wstring GetString();
	void SetString(std::wstring value);
	void SetString(int value);
};

