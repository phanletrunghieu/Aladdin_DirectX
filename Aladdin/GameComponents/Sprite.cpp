#include "Sprite.h"

/*
Sprite::Sprite(LPCWSTR filePath, D3DCOLOR colorKey, RECT sourceRect, int width, int height)
{
	_spriteHandler = Graphics::GetInstance()->GetSpriteHandler();

	_position = D3DXVECTOR3(0, 0, 0);
	_rotation = 0;
	_rotationCenter = D3DXVECTOR2(_position.x, _position.y);
	_translation = D3DXVECTOR2(0, 0);
	_scale = D3DXVECTOR2(1, 1);
	_sourceRect = sourceRect;

	D3DXGetImageInfoFromFile(filePath, &_imageInfo);

	if (width == NULL)
	{
		if (!IsRect(sourceRect))
			_width = _imageInfo.Width;
		else
			_width = sourceRect.right - sourceRect.left;
	}
	else
		_width = width;

	if (height == NULL)
	{
		if (!IsRect(sourceRect))
			_height = _imageInfo.Height;
		else
			_height = sourceRect.bottom - sourceRect.top;
	}
	else
		_height = height;

	if (!IsRect(sourceRect))
	{
		_sourceRect.left = 0;
		_sourceRect.right = _width;
		_sourceRect.top = 0;
		_sourceRect.bottom = _height;
	}

	LPDIRECT3DDEVICE9 device;
	_spriteHandler->GetDevice(&device);

	D3DXCreateTextureFromFileEx(
		device,
		filePath,
		_imageInfo.Width,
		_imageInfo.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		colorKey,
		&_imageInfo,
		NULL,
		&_texture);
}
*/

Sprite::Sprite(LPDIRECT3DTEXTURE9 texture, bool isSourceRight, RECT sourceRect, int width, int height)
{
	_spriteHandler = Graphics::GetInstance()->GetSpriteHandler();
	_texture = texture;

	_position = D3DXVECTOR3(0, 0, 0);
	_rotation = 0;
	_rotationCenter = D3DXVECTOR2(_position.x, _position.y);
	_translation = D3DXVECTOR2(0, 0);
	_scale = D3DXVECTOR2(1, 1);
	_sourceRect = sourceRect;

	_isFlipVertical = _isFlipHorizontal = false;
	_isSourceRight = isSourceRight;

	//get size of LPDIRECT3DTEXTURE9
	D3DSURFACE_DESC surfaceDesc;
	_texture->GetLevelDesc(0, &surfaceDesc);
	size_t size = surfaceDesc.Width * surfaceDesc.Height;

	if (width == NULL)
	{
		if (!IsRect(sourceRect))
			_width = surfaceDesc.Width;
		else
			_width = sourceRect.right - sourceRect.left;
	}
	else
		_width = width;

	if (height == NULL)
	{
		if (!IsRect(sourceRect))
			_height = surfaceDesc.Height;
		else
			_height = sourceRect.bottom - sourceRect.top;
	}
	else
		_height = height;

	if (!IsRect(sourceRect))
	{
		_sourceRect.left = 0;
		_sourceRect.right = _width;
		_sourceRect.top = 0;
		_sourceRect.bottom = _height;
	}

	LPDIRECT3DDEVICE9 device;
	_spriteHandler->GetDevice(&device);
}

Sprite::Sprite()
{
}

Sprite::~Sprite()
{

}

bool Sprite::IsRect(RECT rect)
{
	if (rect.left == rect.right)
		return false;

	if (rect.top == rect.bottom)
		return false;

	return true;
}

void Sprite::Draw(Camera * camera)
{
	//check object in camera or not
	bool isInCamera = camera->IsInCamera(D3DXVECTOR2(_position.x, _position.y), _width, _height);
	if (!isInCamera)
		return;

	//get scale
	_scale.x = _scale.x / abs(_scale.x);
	_scale.y = _scale.y / abs(_scale.y);

	_scale.x *= Graphics::GetInstance()->GetScreenWidth() / camera->GetWidth();
	_scale.y *= Graphics::GetInstance()->GetScreenHeight() / camera->GetHeight();

	// convert position in world to position in camera
	D3DXVECTOR3 newPosition = camera->ConvertPosition(_position.x, _position.y);
	newPosition.z = _position.z;

	Draw(newPosition);
}

void Sprite::Draw(D3DXVECTOR3 position)
{
	D3DXVECTOR3 inPosition = _position;
	if (position != D3DXVECTOR3())
		inPosition = position;

	D3DXVECTOR2 scalingCenter = D3DXVECTOR2(inPosition.x, inPosition.y);

	D3DXMatrixTransformation2D(&_matrix, &scalingCenter, 0, &_scale, &_rotationCenter, _rotation, &_translation);

	D3DXMATRIX oldMatrix;
	_spriteHandler->GetTransform(&oldMatrix);
	_spriteHandler->SetTransform(&_matrix);

	D3DXVECTOR3 center = D3DXVECTOR3(_width / 2, _height / 2, 0);

	_spriteHandler->Draw(_texture,
		&_sourceRect,
		&center,
		&inPosition,
		D3DCOLOR_XRGB(255, 255, 255));

	_spriteHandler->SetTransform(&oldMatrix); // set lai matrix cu~ de Sprite chi ap dung transfrom voi class nay
}

LPDIRECT3DTEXTURE9 Sprite::GetTexture()
{
	return _texture;
}

D3DXIMAGE_INFO Sprite::GetImageInfo()
{
	return _imageInfo;
}

void Sprite::SetSourceRect(RECT rect)
{
	_sourceRect = rect;
}

RECT Sprite::GetSourceRect()
{
	return _sourceRect;
}

int Sprite::GetWidth()
{
	return _width;
}

void Sprite::SetWidth(int width)
{
	_width = width;
}

int Sprite::GetHeight()
{
	return _height;
}

void Sprite::SetHeight(int height)
{
	_height = height;
}

D3DXVECTOR3 Sprite::GetPosition()
{
	return _position;
}

void Sprite::SetPosition(D3DXVECTOR3 pos)
{
	_position = pos;
}

void Sprite::SetPosition(float x, float y)
{
	_position = D3DXVECTOR3(x, y, 0);
}

void Sprite::SetPosition(D3DXVECTOR2 pos)
{
	this->SetPosition(pos.x, pos.y);
}

D3DXVECTOR2 Sprite::GetScale()
{
	return _scale;
}

void Sprite::SetScale(D3DXVECTOR2 scale)
{
	_scale = scale;
}

D3DXVECTOR2 Sprite::GetRotationCenter()
{
	return _rotationCenter;
}

void Sprite::SetRotationCenter(D3DXVECTOR2 rotationCenter)
{
	_rotationCenter = rotationCenter;
}

float Sprite::GetRotation()
{
	return _rotation;
}

void Sprite::SetRotation(float rotation)
{
	_rotation = rotation;
}

void Sprite::FlipHorizontal(bool flag)
{
	if (_isFlipHorizontal != flag)
	{
		_isFlipHorizontal = flag;
		_scale = D3DXVECTOR2(-_scale.x, _scale.y);
	}

}

void Sprite::FlipVertical(bool flag)
{
	if (_isFlipVertical != flag)
	{
		_isFlipVertical = flag;
		_scale = D3DXVECTOR2(_scale.x, -_scale.y);
	}
}

bool Sprite::IsFlipHorizontal()
{
	return _isFlipHorizontal;
}

bool Sprite::IsFlipVertical()
{
	return _isFlipVertical;
}

bool Sprite::IsSourceRight()
{
	return _isSourceRight;
}
