#include "Input.h"

Input* Input::_instance = NULL;

Input::Input()
{
	this->_input = NULL;
	this->_keyboardDevice = NULL;
	this->_mouseDevice = NULL;
	this->_mouseX = this->_mouseY = this->_mouseZ = 0;
	this->_screenWidth = this->_screenHeight = 0;
	this->_hwnd = NULL;

	this->_instance = this;
}

Input::Input(HWND hwnd, int screenWidth, int screenHeight)
{
	this->_input = NULL;
	this->_keyboardDevice = NULL;
	this->_mouseDevice = NULL;
	this->_mouseX = 0;
	this->_mouseY = 0;
	this->_mouseZ = 0;
	this->_screenWidth = screenWidth;
	this->_screenHeight = screenHeight;
	this->_hwnd = hwnd;

	this->_instance = this;
}

Input::~Input()
{
	Release();
}

Input * Input::GetInstance()
{
	return _instance;
}

bool Input::InitMouse()
{
	HRESULT hresult = this->_input->CreateDevice(GUID_SysMouse, &this->_mouseDevice, NULL);
	if (FAILED(hresult))
		return false;

	hresult = this->_mouseDevice->SetDataFormat(&c_dfDIMouse);
	if (hresult != DI_OK)
		return false;

	hresult = this->_mouseDevice->SetCooperativeLevel(this->_hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (hresult != DI_OK)
		return false;

	hresult = this->_mouseDevice->Acquire();
	if (FAILED(hresult))
		return false;

	return true;
}

bool Input::InitKeyboard()
{
	HRESULT hresult = this->_input->CreateDevice(GUID_SysKeyboard, &this->_keyboardDevice, NULL);
	if (FAILED(hresult))
		return false;

	hresult = this->_keyboardDevice->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hresult))
		return false;

	hresult = this->_keyboardDevice->SetCooperativeLevel(this->_hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(hresult))
		return false;

	DIPROPDWORD dipdw;

	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = 256; // Arbitary buffer size

	hresult = this->_keyboardDevice->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
	if (hresult != DI_OK)
		return false;

	hresult = this->_keyboardDevice->Acquire();

	if (FAILED(hresult))
		return false;

	return true;
}

bool Input::Init()
{
	HRESULT hresult = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&_input, NULL);
	if (FAILED(hresult))
		return false;

	if (!InitKeyboard())
		return false;

	if (!InitMouse())
		return false;

	return true;
}

bool Input::Frame()
{
	// Read the current state of the keyboard.
	if (!ReadKeyboard())
		return false;

	// Read the current state of the mouse.
	if (!ReadMouse())
		return false;

	// Process the changes in the mouse and keyboard.
	ProcessInput();

	return true;
}

bool Input::ReadMouse()
{
	// Read the mouse device.
	HRESULT result = this->_mouseDevice->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&this->_mouseState);
	if (FAILED(result))
	{
		// If the mouse lost focus or was not acquired then try to get control back.
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
			this->_mouseDevice->Acquire();
		else
			return false;
	}

	return true;
}

bool Input::ReadKeyboard()
{
	// Read the keyboard device.
	HRESULT result = this->_keyboardDevice->GetDeviceState(sizeof(this->_keyboardState), (LPVOID)&this->_keyboardState);
	if (FAILED(result))
	{
		// If the keyboard lost focus or was not acquired then try to get control back.
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
			this->_keyboardDevice->Acquire();
		else
			return false;
	}

	return true;
}

void Input::ProcessInput()
{
	// Update the location of the mouse cursor based on the change of the mouse location during the frame.
	this->_mouseX += this->_mouseState.lX;
	this->_mouseY += this->_mouseState.lY;
	this->_mouseZ += this->_mouseState.lZ;

	// Ensure the mouse location doesn't exceed the screen width or height.
	if (this->_mouseX < 0)
		this->_mouseX = 0;
	if (this->_mouseY < 0)
		this->_mouseY = 0;
	if (this->_mouseZ < 0)
		this->_mouseZ = 0;

	if (this->_mouseX > this->_screenWidth)
		this->_mouseZ = this->_screenWidth;
	if (this->_mouseY > this->_screenHeight)
		this->_mouseY = this->_screenHeight;
}

bool Input::IsKeyPressed(int keyCode)
{
	// Do a bitwise and on the keyboard state to check if the escape key is currently being pressed.
	if (this->_keyboardState[keyCode] & 0x80)
		return true;

	return false;
}

void Input::Release()
{
	//Release Keyboard
	if (this->_keyboardDevice)
	{
		this->_keyboardDevice->Unacquire();
		this->_keyboardDevice->Release();
		this->_keyboardDevice = NULL;
	}

	//Release Mouse
	if (this->_mouseDevice)
	{
		this->_mouseDevice->Unacquire();
		this->_mouseDevice->Release();
		this->_mouseDevice = NULL;
	}

	//Release Direct input object
	if (this->_input)
	{
		this->_input->Release();
		this->_input = NULL;
	}
}

bool Input::MouseButtonDown(int button)
{
	return ((this->_mouseState.rgbButtons[button] & 0x80) != 0);
}

int Input::GetMouseX()
{
	return this->_mouseX;
}

int Input::GetMouseY()
{
	return this->_mouseY;
}

int Input::GetMouseZ()
{
	return this->_mouseZ;
}

void Input::GetMouseLocation(int & mouseX, int & mouseY)
{
	mouseX = this->_mouseX;
	mouseY = this->_mouseY;
}

void Input::GetMouseLocation(int & mouseX, int & mouseY, int & mouseZ)
{
	mouseX = this->_mouseX;
	mouseY = this->_mouseY;
	mouseZ = this->_mouseZ;
}
