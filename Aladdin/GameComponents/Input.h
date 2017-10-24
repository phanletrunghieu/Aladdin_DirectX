#pragma once

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

#define DIRECTINPUT_VERSION 0x0800

#include <dinput.h>;

class Input
{
private:
	static Input* _instance;

	IDirectInput8 *_input;
	IDirectInputDevice8 *_keyboardDevice;
	IDirectInputDevice8 *_mouseDevice;
	unsigned char _keyboardState[256];
	DIMOUSESTATE2 _mouseState;

	HWND _hwnd;
	int _mouseX, _mouseY, _mouseZ;
	int _screenWidth, _screenHeight;

	bool InitMouse();
	bool InitKeyboard();

	bool ReadMouse();
	bool ReadKeyboard();
	void ProcessInput();
public:
	Input();
	Input(HWND hwnd, int screenWidth, int screenHeight);
	~Input();

	static Input* GetInstance();

	bool Init();
	bool Frame();
	bool IsKeyPressed(int keyCode);
	void Release();

	bool MouseButtonDown(int button);
	int GetMouseX();
	int GetMouseY();
	int GetMouseZ();
	void GetMouseLocation(int& mouseX, int& mouseY);
	void GetMouseLocation(int& mouseX, int& mouseY, int& mouseZ);
};

