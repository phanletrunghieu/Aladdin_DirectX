#include "Text.h"

Text::Text()
{
}

Text::Text(std::wstring str, unsigned int width, unsigned height, unsigned int weight, bool italic, DWORD alignment, D3DCOLOR color, LPCWSTR fontName)
{
	_spriteHandler = Graphics::GetInstance()->GetSpriteHandler();

	_string = str;
	_width = width;
	_height = height;
	_alignment = alignment;
	_color = color;
	_fontName = fontName;
	_weight = weight;
	_italic = italic;

	D3DXCreateFont(
		Graphics::GetInstance()->GetDevice(),
		_height,
		_width,
		_weight,
		0, // Miplevels
		_italic,
		DEFAULT_CHARSET, // CharSet
		OUT_DEFAULT_PRECIS, // OutputPrecision
		ANTIALIASED_QUALITY, // Quality
		DEFAULT_PITCH | FF_DONTCARE, // Pitch and Family
		_fontName,      // facename
		&_font);
}

Text::~Text()
{
	if (_font) {
		_font->Release();
		_font = NULL;
	}
}

void Text::Draw(D3DXVECTOR2 position)
{
	RECT rect;
	rect.left = position.x - _width / 2.0f;
	rect.top = position.y - _height / 2.0f;
	rect.right = rect.left + _width;
	rect.bottom = rect.top + _height;
	_font->DrawTextW(_spriteHandler, _string.c_str(), -1, &rect, _alignment, _color);
}

std::wstring Text::GetString()
{
	return _string;
}

void Text::SetString(std::wstring value)
{
	_string = value;
}

void Text::SetString(int value)
{
	_string = std::to_wstring(value);
}
